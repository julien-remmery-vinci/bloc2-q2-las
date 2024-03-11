#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "makegen_utils.h"

void* checkNull(void* v) {
	if(v == NULL) {
		perror("Error");
		return NULL;
	}
	return v;
}

void checkNullExit(void* v) {
	if(v == NULL) {
		perror("Error");
		exit(1);
	}
}

void checkArgs(int nbArgs) {
	if(nbArgs == 1){
		printf("Error: please provide a file in arguments\n");
		exit(1);
	}
}

bool containsFile(char** t, char* toCompare, int size) {
	for (int i = 0; i < size; ++i){
		if(strcmp(t[i], toCompare) == 0)
			return true;
	}
	return false;
}

void addFile(char*** t, char* toAdd, int* size) { 
	//*t = realloc(*t, (*size)+1*sizeof(char*));
	(*t)[*size] = (char*) malloc((strlen(toAdd)+1)*sizeof(char));
	checkNull((*t)[*size]);
	strcpy((*t)[*size], toAdd);
	(*size)++;
}

char* getFileName(char* b) {
	char* filename = (char*)malloc(MAX_LENGTH*sizeof(char));
	checkNullExit(filename);
	strncpy(filename, b+QUOTE_POS+1, MAX_LENGTH);
	int size = strlen(filename)-4;
	filename[size] = '\0';
	return filename;
}

void getFiles(FILE* f, char*** t, int* n) {
	if(f != NULL) {
		*n = 0;
		if((*t) == NULL) {
			(*t) = (char**)malloc(0*sizeof(char*));
			checkNullExit((*t));
		}
		char buff[MAX_LENGTH+1];
		while(fgets(buff, MAX_LENGTH, f)) {
			if(strncmp(buff, "#include \"", 10) == 0) {
				char* filename = getFileName(buff);
				(*t) = realloc((*t), (*n)+1*sizeof(char**));
				checkNullExit((*t));
				(*t)[*n] = (char*)malloc(strlen(filename)+1*sizeof(char));
				checkNullExit((*t)[*n]);
				strcpy((*t)[*n], filename);
				free(filename);
				(*n)++;
			}
			else if(strncmp(buff, "#d", 2) == 0) break;
		}
	}
}

void addGenText(FILE* f) {
	fputs(TOP_TEXT, f);
}

void addFlags(FILE* f) {
	fprintf(f, "%s\n\n", FLAGS);
}

char* addAllRule(FILE* f, int n, const char** t) {
	char* text = NULL;
	for (int i = 0; i < n; ++i) {
		int size = strlen(t[i])-2;
		text = realloc(text, size+1*sizeof(char));
		checkNullExit(text);
		char* filename = (char*)malloc(size*sizeof(char));
		checkNullExit(filename);
		strncpy(filename, t[i], size);
		strcat(text, filename);
		free(filename);
		strcat(text, " ");
	}
	fprintf(f, "all: %s\n\n", text);
	return text;
}

void addCleanRule(FILE* f, bool o, char* s) {
	fputs("clean:\n", f);
	if(o) fprintf(f, "\trm *.o\n");
	fprintf(f, "\trm %s\n", s);
}

void addCompile(char* fname, FILE* fout, char** oTab, int* oSize) {
	char* fext = (char*)malloc(strlen(fname)+3*sizeof(char));
	checkNullExit(fext);
	strcpy(fext, fname);
	strcat(fext, ".c");
	FILE* fin = fopen(fext, "r");
	checkNullExit(fin);
	int nbFiles;
	char** tab = NULL;
	getFiles(fin, &tab, &nbFiles);
	fclose(fin);
	if(nbFiles == 1) {
		//ECRIRE COMPILATION CAR DERNIER FICHIER TROUVER
		fprintf(fout, "%s.o: %s.c %s.h\n", tab[0], tab[0], tab[0]);
		fprintf(fout, "\tgcc $(CFLAGS) -c %s.c\n\n", tab[0]);
		if(*oTab == NULL) {
			*oSize = 0;
			*oTab = (char*)calloc((*oSize), sizeof(char));
			checkNullExit(*oTab);
		}
		*oSize += strlen(tab[0])+4;
		*oTab = realloc(*oTab, (*oSize)*sizeof(char));
		checkNullExit(*oTab);
		strcat(*oTab, tab[0]);
		strcat(*oTab, ".h ");
	}
	else {
		char* reqStr = (char*)malloc(0*sizeof(char));
		checkNullExit(reqStr);
		int size = 0;
		for (int i = 0; i < nbFiles; ++i) {
			size += strlen(tab[i])+3;
			reqStr = realloc(reqStr, size*sizeof(char));
			checkNullExit(reqStr);
			strcat(reqStr, tab[i]);
			strcat(reqStr, ".h ");
			addCompile(tab[i], fout, oTab, oSize);
		}
		//ECRIRE COMPILATION AVEC TOUT LES FICHIERS TROUVES
		fprintf(fout, "%s.o: %s.c %s.h %s\n", fname, fname, fname, reqStr);
		free(reqStr);
		fprintf(fout, "\tgcc $(CFLAGS) -c %s.c\n\n", fname);

		for (int i = 0; i < nbFiles; ++i)
			free(tab[i]);
		free(tab);
	}
}

char* cutExtension(const char* s) {
	char* name = (char*)malloc(strlen(s)-2*sizeof(char));
	checkNullExit(name);
	strncpy(name, s, strlen(s)-2);
	return name;
}

void buildFile(int n, const char** t) {
	checkArgs(n);

	FILE* f = fopen(GENERATED_NAME, "w");
	checkNullExit(f);

	addGenText(f);

	addFlags(f);

	int nbExec = n-1;
	char* generatedExec = NULL;
	if(nbExec > 1) {
		generatedExec = addAllRule(f, nbExec, t);
		checkNullExit(generatedExec);
	}
	else {
		char* filename = (char*)malloc(strlen(t[0])+1*sizeof(char));
		checkNullExit(filename);
		strcpy(filename, t[0]);
		generatedExec = (char*)malloc(strlen(filename)-1*sizeof(char));
		checkNullExit(generatedExec);
		strcpy(generatedExec, strtok(filename, "."));
		free(filename);
	}

	bool oFilesToClean = false;

	for (int i = 0; i < nbExec; ++i)
	{
		FILE* fin = fopen(t[i], "r");
		checkNullExit(fin);
		int nbFiles;
		char** files = NULL;
		getFiles(fin, &files, &nbFiles);
		fclose(fin);
		
		char* reqStr = (char*)malloc(0*sizeof(char));
		checkNullExit(reqStr);
		int size = 0;
		for (int i = 0; i < nbFiles; ++i) {
			size += strlen(files[i])+4;
			reqStr = realloc(reqStr, size*sizeof(char));
			checkNullExit(reqStr);
			strcat(reqStr, files[i]);
			strcat(reqStr, ".o ");
			oFilesToClean = true;
		}

		char* fname = cutExtension(t[i]);
		fprintf(f, "%s: %s.o %s\n", fname, fname, reqStr);
		fprintf(f, "\tgcc $(CFLAGS) -o %s %s.o %s\n\n", fname, fname, reqStr);
		free(reqStr);

		char* oTab = NULL;
		int oSize;
		addCompile(fname, f, &oTab, &oSize);

		fprintf(f, "%s.o: %s.c %s\n", fname, fname, oTab);
		fprintf(f, "\tgcc $(CFLAGS) -c %s.c\n\n", fname);

		free(fname);
	}

	addCleanRule(f, oFilesToClean, generatedExec);
	free(generatedExec);

	fclose(f);
}