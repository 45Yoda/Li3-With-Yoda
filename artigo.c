#include "./headers/artigo.h"#include <string.h>#include <stdio.h>#include <stdlib.h>#define MAXSIZE 64/*1- todos os artigos (contar i's)2-artigos unicos (contar nodos)3-nr revisoes (timestamps diferentes)4- autores mais revisoes (guardar autores e revisores de cada artigo)5-autor com determinado id6-artigos mais bytes7-artigo com um id8-mais words( conta ultima revisao)9-artigos com prefixo (conta titulo ultima revisão)10-timestamp certa revisao de um artigo*/struct artigo {	char* titulo; //atualizar a cada revisao	int n; //nr de vezes que artigo aparece	char** timestamp; //guarda todos os timestamps por ordem de revisao	char** autores; //autores de todas as revisoes por ordem de revisao	long* autId; // id dos autores por ordem de revisao	long bytes; //atualizar a cada revisao	long words; //atualizar a cada revisao};Artigo init_Artigo (int size) {	Artigo novo = (Artigo) malloc(sizeof(struct artigo));	int i;	novo->titulo=NULL;	novo->n=0;	novo->timestamp=malloc(size *sizeof(char*));	novo->autores=malloc(size *sizeof(char*));	novo->autId=malloc(size *sizeof(long));	for(i=0; i<size;i++){		novo->timestamp[i]=malloc(MAXSIZE);		novo->autores[i]=malloc(MAXSIZE);	}	novo->bytes=0;	novo->words=0;}char* getTitulo (Artigo a) {	return a->titulo;}void setTitulo(Artigo a, char* title){	a->titulo = title;	//printf("%s\n",title );}int getN(Artigo a){	return a->n;}void incrN(Artigo a){	 a->n++;}void getTimeStamp(Artigo a, char* *t[]){	int b=getN(a),i;	*t=malloc(b*sizeof(char*));	for(i=0;i<b;i++){		*t[i]=strdup(a->timestamp[i]);		//printf("%s\n",t[i]);	}}void setTimeStamp(Artigo a, char* time,int pos){	//int i=0;	a->timestamp[pos] = time;	//for(i=0;i<1;i++)	//	printf("%s\n", a->timestamp[i]);}void getAutores(Artigo a,char** aut[]) {	int b=getN(a),i;	*aut=malloc(b*sizeof(char*));	for(i=0;i<b;i++) {		*aut[i]=strdup(a->autores[i]);		//printf("%s\n",aut[i]);	}}void setAutores(Artigo a, char* autor, int pos){	a->autores[pos]=autor;	//printf("%s\n",a->autores[pos]);}void getAutId(Artigo a,long* c[]){	int b=getN(a),i;	*c=(long*)malloc(b*sizeof(long));	for(i=0;i<b;i++) {		*c[i]=a->autId[i];		//printf("%ld\n", c[i]);	}}void setAutId(Artigo a, long id, int pos){	a->autId[pos]=id;	//printf("%ld\n",a->autId[pos]);}long getBytes(Artigo a){	return a->bytes;}void setBytes(Artigo a, long bytes){	a->bytes=bytes;}long getWords(Artigo a){	return a->words;}void setWords(Artigo a, long words){	a->words=words;}