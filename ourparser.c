#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "./headers/ourparser.h"

void parseFinal(long idArt,char* title,char* timestamp,char* username,long id,long wcount,long bcount,Avl a){
    void* art;
    int c;
    art= (Artigo) getAvlEstrutura(a,idArt);
    //TODO fazer funçoes dentro do artigo.c que façam isto;
    setTitulo(art,title);
    //printf("%s\n",getTitulo(art));
    int i = getN(art);
    setTimeStamp(art,timestamp,i);
    //getTimeStamp(art,puta);
    //printf("%s\n",puta[i]);
    setAutores(art,username,i);
    //getAutores(art,puta);
    //printf("%s\n",puta[i]);
    setAutId(art,id,i);
    //getAutId(art,whore[i]);

    //a->tree->info->bytes=bcount;
    //a->tree->info->words=wcount;

    incrN(art); //funcemina


    //printf("----------------------------------------------\n" );

}

void parseText(xmlDocPtr doc,xmlNodePtr cur, long idArt,char* title,char* timestamp,char* username, long id,Avl a){
    long wcount=0;
    long bcount=0;
    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if((!xmlStrcmp(cur->name,(const xmlChar *) "text")));
        //TODO fazer o word count e o byte count;
    }
    parseFinal(idArt,title,timestamp,username,id,wcount,bcount,a);
}


void parseContributor(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,char* timestamp,Avl a){

    long id;
    char *username;
    xmlNodePtr aux;
    int artigos = 0;

    aux = cur->parent;

    for(cur= cur->xmlChildrenNode; cur;cur = cur->next){

        if(!xmlStrcmp(cur->name,(const xmlChar *)"username"))
            username = (char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

        if(!xmlStrcmp(cur->name,(const xmlChar *) "id"))
            id = atol((char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1));
    }

    parseText(doc,aux,idArt,title,timestamp,username,id,a);
    return;
}


void parseRevision(xmlDocPtr doc, xmlNodePtr cur,long idArt,char* title,Avl a){
    char* timestamp;
    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if((!xmlStrcmp(cur->name,(const xmlChar *) "timestamp")))
            timestamp=(char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        if((!xmlStrcmp(cur->name,(const xmlChar *) "contributor")))
            parseContributor(doc,cur,idArt,title,timestamp,a);
        }

    return;
}


void parseDoc(char *docname,int argc, Avl a){

    long idArt;
    clock_t tpf;

    xmlChar *id;
    xmlChar *title;
    char* idA;
    xmlDocPtr doc;
    xmlNodePtr cur;
    xmlNodePtr aux;


    tpf =clock();

    doc = xmlParseFile(docname);

    tpf =clock() -tpf;

    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);

    if (doc == NULL){
        fprintf(stderr,"Document not parsed sucessfully. \n");
        return;
    }

    cur = xmlDocGetRootElement(doc);

    if(cur==NULL){
        perror("Empty document\n"); //usar perror funciona?
        xmlFreeDoc(doc);
        return;
    }

    cur = cur->xmlChildrenNode;
    cur = cur->next;

    for(cur;cur!=NULL;cur=cur->next){
        aux=cur;
        if(!xmlStrcmp(cur->name,(const xmlChar *) "page")){
            for(cur=cur->xmlChildrenNode; cur; cur= cur->next){

                if((!xmlStrcmp(cur->name,(const xmlChar *) "title"))){
                    title = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

                }

                if((!xmlStrcmp(cur->name,(const xmlChar *) "id"))){
                    idA=(char*) xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
                    idArt= atol(idA);
                    if (!avlSearch(a,idArt)) {
                        Artigo stArt = init_Artigo(argc);
                        a=insertAvl(a,idArt,stArt);
                    }
                }
                if((!xmlStrcmp(cur->name,(const xmlChar *) "revision"))){
                    parseRevision(doc,cur,idArt,title,a);
                }

            }
        }

        cur=aux->next;
        //printf("%s = %ld\n",title,idArt);

    }
    xmlFreeDoc(doc);
    return;
}

int main(int argc, char **argv){
    int i;
    char *docname;
    clock_t tpf;

    if(argc <= 1){
        perror("Uso incorrecto\n");
        return 0;
    }
    Avl a = initAvl();

    tpf =clock();
    for(i=1;argc>1;argc--,i++){
        docname=argv[i];
        parseDoc(docname,argc,a);
    }
    //29128
    int z=0;
    Artigo art = getAvlEstrutura(a,29128);
    char* t=getTitulo(art);
    printf("%s\n",t);
    int nn = getN(art);
    printf("%d\n", nn);
    char** time;
    char** aut;
    long* autid;
    getTimeStamp (art,time); 
    getAutores(art,aut);
    getAutId(art,autid);
    //if (autid[0]==29662635) printf("leu\n");
    tpf =clock() -tpf;
    printf("Demorou %f segundos a ler\n",((float)tpf)/CLOCKS_PER_SEC);
    return 1;
}
