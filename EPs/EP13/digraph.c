/****************************************************************
    Nome: Caio Túlio de Deus Andrade
    NUSP: 9797232

    Ao preencher esse cabeçalho com o meu nome e o meu número USP,
    declaro que todas as partes originais desse exercício programa (EP)
    foram desenvolvidas e implementadas por mim e que portanto não 
    constituem desonestidade acadêmica ou plágio.
    Declaro também que sou responsável por todas as cópias desse
    programa e que não distribui ou facilitei a sua distribuição.
    Estou ciente que os casos de plágio e desonestidade acadêmica
    serão tratados segundo os critérios divulgados na página da 
    disciplina.
    Entendo que EPs sem assinatura devem receber nota zero e, ainda
    assim, poderão ser punidos por desonestidade acadêmica.

    Abaixo descreva qualquer ajuda que você recebeu para fazer este
    EP.  Inclua qualquer ajuda recebida por pessoas (inclusive
    monitoras e colegas). Com exceção de material de MAC0323, caso
    você tenha utilizado alguma informação, trecho de código,...
    indique esse fato abaixo para que o seu programa não seja
    considerado plágio ou irregular.

    Exemplo:

        A monitora me explicou que eu devia utilizar a função xyz().

        O meu método xyz() foi baseada na descrição encontrada na 
        página https://www.ime.usp.br/~pf/algoritmos/aulas/enumeracao.html.

    Descrição de ajuda ou indicação de fonte:

    A correção do problema no toString relatada a baixo foi feita com outro aluno,
    Leandro Rodrigues.


    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:

    Por alguma razão, meu programa ,durante o teste do reverseDigraph no unit test,
    imprimia o grafo original e depois o grafo revertido, não consegui localizar a
    razão desse erro. Copiando o conteúdo da string para outra menor parece consertar o problema

****************************************************************/

/*
 * MAC0323 Algoritmos e Estruturas de Dados II
 * 
 * ADT Digraph implementada atrevés de vetor de listas de adjacência.
 * As listas de adjacência são bag de ints que são mais restritos 
 * que as bags genéricas do EP12. Veja a api bag.h e simplifique 
 * o EP12 de acordo. 
 *  
 * Busque inspiração em: 
 *
 *    https://algs4.cs.princeton.edu/42digraph/ (Graph representation)
 *    https://algs4.cs.princeton.edu/42digraph/Digraph.java.html
 * 
 * DIGRAPH
 *
 * Digraph representa um grafo orientado de vértices inteiros de 0 a V-1. 
 * 
 * As principais operações são: add() que insere um arco no digrafo, e
 * adj() que itera sobre todos os vértices adjacentes a um dado vértice.
 * 
 * Arcos paralelos e laços são permitidos.
 * 
 * Esta implementação usa uma representação de _vetor de listas de adjacência_,
 * que  é uma vetor de objetos Bag indexado por vértices. 

 * ATENÇÃO: Por simplicidade esses Bag podem ser int's e não de Integer's.
 *
 * Todas as operações consomen no pior caso tempo constante, exceto
 * iterar sobre os vértices adjacentes a um determinado vértice, cujo 
 * consumo de tempo é proporcional ao número de tais vértices.
 * 
 * Para documentação adicional, ver 
 * https://algs4.cs.princeton.edu/42digraph, Seção 4.2 de
 * Algorithms, 4th Edition por Robert Sedgewick e Kevin Wayne.
 *
 */

/* interface para o uso da funcao deste módulo */
#include "digraph.h"
#include "bag.h"     /* add() e itens() */
#include <stdio.h>   /* fopen(), fclose(), fscanf(), ... */
#include <stdlib.h>  /* free() */
#include <string.h>  /* memcpy() */
#include "util.h"    /* emalloc(), ecalloc() */

#undef DEBUG
#ifdef DEBUG
#include <stdio.h>   /* printf(): para debuging */
#endif

/*----------------------------------------------------------*/
/* 
 * Estrutura básica de um Digraph
 * 
 * Implementação com vetor de listas de adjacência.
 */
struct digraph 
{
    int v;
    int e; 
    int bagSize;
    int* inDegree;
    Bag* adjacencyList;
};

/*------------------------------------------------------------*/
/* 
 * Protótipos de funções administrativas: tem modificador 'static'
 * 
 */

/*-----------------------------------------------------------*/
/*
 *  newDigraph(V)
 *
 *  RECEBE um inteiro V.
 *  RETORNA um digrafo com V vértices e 0 arcos.
 * 
 */
Digraph newDigraph(int V) {
    Digraph newD = malloc(sizeof(struct digraph));
    newD->inDegree = calloc(V, sizeof(int));
    newD->v = V;
    newD->e = 0;
    newD->adjacencyList = malloc(V * sizeof(Bag));
    for(int i = 0; i < V; i++) {
        newD->adjacencyList[i] = newBag();
    }
    Bag myBag = newBag();
    newD->bagSize = sizeof(myBag);
    freeBag(myBag);
    return newD;
}

/*-----------------------------------------------------------*/
/*
 *  cloneDigraph(G)
 *
 *  RECEBE um digrafo G.
 *  RETORNA um clone de G.
 * 
 */
Digraph cloneDigraph(Digraph G) { 
    int index;
    int j;
    vertex* reverse;
    Digraph cloneDigraph = newDigraph(G->v);

    for(int i = 0; i < G->v; i++) {
        reverse = malloc(sizeof(outDegree(G, i)));
        for (index = itens(G->adjacencyList[i], TRUE), j = 0;
            index != -1;
            index = itens(G->adjacencyList[i], FALSE))
        {    
            reverse[j++] = index; // preserva a ordem da lista de adjacencia original
        }

        for(j = 0; j < outDegree(G, i); j++) {
            addEdge(cloneDigraph, i, reverse[outDegree(G,i) - j]);
        }

        free(reverse);
    }

    return cloneDigraph;
}

/*-----------------------------------------------------------*/
/*
 *  reverseDigraph(G)
 *
 *  RECEBE um digrafo G.
 *  RETORNA o digrafo R que é o reverso de G: 
 *
 *      v-w é arco de G <=> w-v é arco de R.
 * 
 */
Digraph
reverseDigraph(Digraph G)
{
    Digraph reversedDigraph = newDigraph(G->v);
    reversedDigraph->e = G->e;
    
    for(int i = 0; i < G->v; i++) {
        for 
            (
            int index = itens(G->adjacencyList[i], TRUE); 
            index != -1; 
            index = itens(G->adjacencyList[i], FALSE) 
            ) 
        {
            add(reversedDigraph->adjacencyList[index],i);
        }
        reversedDigraph->inDegree[i] = size(G->adjacencyList[i]);
    }
    return reversedDigraph;
}

/*-----------------------------------------------------------*/
/*
 *  readDigraph(NOMEARQ)
 *
 *  RECEBE uma stringa NOMEARQ.
 *  RETORNA o digrafo cuja representação está no arquivo de nome NOMEARQ.
 *  O arquivo contém o número de vértices V, seguido pelo número de arestas E,
 *  seguidos de E pares de vértices, com cada entrada separada por espaços.
 *
 *  Veja os arquivos  tinyDG.txt, mediumDG.txt e largeDG.txt na página do 
 *  EP e que foram copiados do algs4, 
 * 
 */
Digraph
readDigraph(String nomeArq)
{
    FILE* fp;
    Digraph myGraph;
    int V,E;
    vertex from, to;
    from = to = 0;

    String Vs = malloc(sizeof(char)*10);
    String Es = malloc(sizeof(char)*10);

    fp = fopen(nomeArq, "r");
    char ch;
    if(fp == NULL) {
        printf("Erro na abertura do arquivo...\n");
        return NULL;
    }
    else {
        
        fscanf(fp, "%s", Vs);
        fscanf(fp, "%s", Es);

        V = atoi(Vs);
        E = atoi(Es);

        myGraph = newDigraph(V);
        myGraph->e = E;

        while((ch = fgetc(fp)) != EOF) {
            fscanf(fp, "%d", &from);
            fscanf(fp, "%d", &to);
            add(myGraph->adjacencyList[from],to);
        }
    }
    free(Vs);
    free(Es);
    Vs = Es = NULL;
    
    fclose(fp);
    return myGraph;
}


/*-----------------------------------------------------------*/
/*
 *  freeDigraph(G)
 *
 *  RECEBE um digrafo G e retorna ao sistema toda a memória 
 *  usada por G.
 *
 */
void freeDigraph(Digraph G) {
    for(int i = 0; i < G->v; i++) {
        freeBag(G->adjacencyList[i]);
        G->adjacencyList[i] = NULL;
    }
    free(G->inDegree);
    free(G->adjacencyList);
    G->adjacencyList = NULL;
    free(G);
}    

/*------------------------------------------------------------*/
/*
 * OPERAÇÕES USUAIS: 
 *
 *     - vDigraph(), eDigraph(): número de vértices e arcos
 *     - addEdge(): insere um arco
 *     - adj(): itera sobre os vizinhos de um dado vértice
 *     - outDegree(), inDegree(): grau de saída e de entrada
 *     - toString(): usada para exibir o digrafo 
 */

/*-----------------------------------------------------------*/
/* 
 *  VDIGRAPH(G)
 *
 *  RECEBE um digrafo G e RETORNA seu número de vertices.
 *
 */
int
vDigraph(Digraph G)
{
    return G->v;
    
}

/*-----------------------------------------------------------*/
/* 
 *  EDIGRAPH(G)
 *
 *  RECEBE um digrafo G e RETORNA seu número de arcos (edges).
 *
 */
int
eDigraph(Digraph G)
{
    return G->e;
}

/*-----------------------------------------------------------*/
/*
 *  addEdge(G, V, W)
 * 
 *  RECEBE um digrafo G e vértice V e W e INSERE o arco V-W  
 *  em G.
 *
 */
void addEdge(Digraph G, vertex v, vertex w) {
    add(G->adjacencyList[v], w);
    G->inDegree[w]++;
    G->e++;
}    


/*-----------------------------------------------------------*/
/* 
 *  ADJ(G, V, INIT)
 * 
 *  RECEBE um digrafo G, um vértice v de G e um Bool INIT.
 *
 *  Se INIT é TRUE,  ADJ() RETORNA o primeiro vértice na lista de adjacência de V.
 *  Se INIT é FALSE, ADJ() RETORNA o sucessor na lista de adjacência de V do 
 *                   último vértice retornado.
 *  Se a lista de adjacência de V é vazia ou não há sucessor do último vértice 
 *  retornada, ADJ() RETORNA -1.
 *
 *  Se entre duas chamadas de ADJ() a lista de adjacência de V é alterada, 
 *  o comportamento é  indefinido. 
 *  
 */
int 
adj(Digraph G, vertex v, Bool init)
{
    return itens(G->adjacencyList[v], init);
}

/*-----------------------------------------------------------*/
/*
 *  outDegree(G, V)
 * 
 *  RECEBE um digrafo G e vértice V.
 *  RETORNA o número de arcos saindo de V.
 *
 */
int
outDegree(Digraph G, vertex v)
{
    return size(G->adjacencyList[v]);
}

/*-----------------------------------------------------------*/
/*
 *  inDegree(G, V)
 * 
 *  RECEBE um digrafo G e vértice V.
 *  RETORNA o número de arcos entrando em V.
 *
 */
int
inDegree(Digraph G, vertex v)
{
    return G->inDegree[v];
}


/*-----------------------------------------------------------*/
/*
 *  toString(G)
 * 
 *  RECEBE um digrafo G.
 *  RETORNA uma string que representa G. Essa string será usada
 *  para exibir o digrafo: printf("%s", toString(G)); 
 *    
 *  Sigestão: para fazer esta função inspire-se no método 
 *  toString() da classe Digraph do algs4.
 */
String
toString(Digraph G)
{
    String final;
    String graphToString = malloc(sizeof(char) * (G->v*G->v + 1000)); 
    sprintf(graphToString + strlen(graphToString), " %d vertices, %d edges\n",G->v, G->e);

    for(vertex i = 0; i < G->v; i++) {
        sprintf(graphToString + strlen(graphToString), "%d :", i);
        for (int index = itens(G->adjacencyList[i], TRUE);
            index != -1;
            index = itens(G->adjacencyList[i], FALSE))
        {    
            sprintf(graphToString + strlen(graphToString), "%d ",index);
        }
        sprintf(graphToString+strlen(graphToString), "\n");
    }
    final = malloc(sizeof(char) * strlen(graphToString) + 1); // retorna uma string
    // contendo apenas o conteudo de graphToString,evitando retornar uma string muito grande
    strcpy(final, graphToString);
    free(graphToString);
    graphToString = NULL;

    return final;
}
/*------------------------------------------------------------*/
/* 
 * Implementaçao de funções administrativas: têm o modificador 
 * static.
 */

