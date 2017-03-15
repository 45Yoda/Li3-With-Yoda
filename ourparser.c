#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

void parseContributor(int number, xmlDocPtr doc, xmlNodePtr cur){

    xmlChar *id;
    xmlChar *username;
    xmlChar *pageTitle;
    xmlChar *ip;
    xmlNodePtr aux;
    int ipMode = 0;

    aux = cur->parent;

    for(cur= cur->xmlChildrenNode; cur;cur = cur->next){
        if(!xmlStrcmp(cur->name,(const xmlChar *)"ip")){
            ipMode = 1;
            ip = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        }
        if(!xmlStrcmp(cur->name,(const xmlChar *)"username"))
            username = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);

        if(!xmlStrcmp(cur->name,(const xmlChar *) "id"))
            id = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
    }

    for(aux; (xmlStrcmp(aux->name,(const xmlChar *)"title")); aux=aux->prev);

    pageTitle = xmlNodeListGetString(doc,aux->xmlChildrenNode,1);

    if(!ipMode){
        printf("O contribuidor numero %d, username %s e o id %s, atualizou o artigo %s .\n",number,username,id,pageTitle);
        xmlFree(id);
        xmlFree(username);
        xmlFree(pageTitle);
    }else{
        printf("O ip %s, contribui para o artigo %s\n",ip,pageTitle);
        xmlFree(ip);
        xmlFree(pageTitle);
    }

    return;
}

void parseRevision(int number, xmlDocPtr doc, xmlNodePtr cur){

    for(cur=cur->xmlChildrenNode;cur;cur=cur->next){
        if((!xmlStrcmp(cur->name,(const xmlChar *) "contributor")))
            parseContributor(number,doc,cur);
        }

    return;
}


void parseDoc(char *docname){

    int number = 0;

    clock_t tpf;

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

    for(cur;cur;cur=cur->next,number++){
        aux=cur;
        if(!xmlStrcmp(cur->name,(const xmlChar *) "page")){
            for(cur=cur->xmlChildrenNode; cur; cur= cur->next){
                if((!xmlStrcmp(cur->name,(const xmlChar *) "revision"))){
                    parseRevision(number,doc,cur);
                }
            }
        }
        cur=aux->next;
    }

    xmlFreeDoc(doc);
    return;
}

int main(int argc, char **argv){

    char *docname;

    if(argc <= 1){
        perror("Uso incorrecto\n");
        return 0;
    }

    docname=argv[1];
    parseDoc(docname);

    return 1;
}
