#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "./headers/ourparser.h"
#include "./headers/artigo.h"
#include "./headers/registo.h"
#include "./headers/contribuidor.h"

long contaArt(Registo reg,Avl a, NODO n) {
    long t=0;
    if (n!=NULL){
        void* artigo;
        long id = getId(n);
        artigo = getRegArtEstrutura(reg,id);
        t=getN(artigo)+contaArt(reg,a,getNodoEsq(n))+contaArt(reg,a,getNodoDir(n));
    }
    return t;
}

//interrogação nº1 que devolve o numero total de artigos nos backups
long all_Articles(Registo reg){
    long i,t=0;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(reg,i);
        NODO n = getNodo(a);
        t+= contaArt(reg,a,n);
    }
    return t;

}

//interrogação nº2 que retorna o numero total de artigos unicos 
long unique_articles( Avl a){
    return totalRegElemsArtigos(reg);
}

long contaRev(Registo reg, Avl a, NODO n) {
    long t=0;
    int i,c=1;
    if (n!=NULL){
        void* artigo;
        long id = getId(n);
        artigo = getRegArtEstrutura(reg,id);
        long *revid=malloc(getN(artigo)*sizeof(long*));
        getRevId(artigo,revid);
        for (i=0;i<getN(artigo)-1;i++) {
            if (revid[i]!=revid[i+1]) c++;
        }
        t= c+contaRev(reg,a,getNodoEsq(n))+contaRev(reg,a,getNodoDir(n));
        free(revid);
    }
    return t;
}

//interrogação nº3 que retorna o numero total de revisões
long all_revisions(Registo reg) {
    long i,t=0;
    for(i=0;i<10;i++){
        Avl a = getRegArtigos(reg,i);
        NODO n = getNodo(a);
        t+= contaRev(reg,a,n);
    }
    return t;

}

//interrogação nº4 que retorna o top 10 contribuidores 
long* top_10_contributors(Registo reg){}


//interrogação nº5 que retorna o username de um contribuidor com determinado id
char* contributor_name(long contributor_id, Registo reg){
    void* cont = getRegContEstrutura(reg,contributor_id);
    char* user = malloc(sizeof(char*));
    getUsername(cont, user);
    return user;
}

//interrogação nº7 que retorna o titulo de um artigo com determinado id
char* article_title(long id,Registo reg) {
    void* artigo = getRegArtEstrutura(reg,id);
    return getTitulo(artigo);
}

//interrogação nº10 que retorna o timestamp de uma certa revisão de um artigo
char* article_timestamp(long article_id,long revision_id,Registo reg) {
    void* artigo = getRegArtEstrutura(reg,article_id);
    long *revid=malloc(getN(artigo)*sizeof(long*));
    char* timeSt = NULL;
    int i;
    getRevId(artigo,revid);
    for (i=0;i<getN(artigo);i++) {
        if (revid[i]==revision_id) {
            char** times = malloc(getN(artigo)*sizeof(char*));
            getTimeStamp(artigo,times);
            timeSt = times[i];
            free(times);
            }
    }
    free(revid);
    return timeSt;
}