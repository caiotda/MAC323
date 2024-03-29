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

    Descrição de ajuda ou indicação de fonte:



    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:

****************************************************************/



/*
 * MAC0323 Estruturas de Dados e Algoritmo II
 * 
 * Tabela de simbolos implementada atraves de vetores ordenados 
 * redeminsionaveis 
 *
 *     https://algs4.cs.princeton.edu/31elementary/BinarySearchST.java.html
 * 
 * As chaves e valores desta implementaÃ§Ã£o sÃ£o mais ou menos
 * genÃ©ricos
 */

/* interface para o uso da funcao deste mÃ³dulo */
#include "binarysearchst.h"  

#include <stdlib.h>  /* free() */
#include <string.h>  /* memcpy() */
#include "util.h"    /* emalloc(), ecalloc() */

#undef DEBUG
#ifdef DEBUG
#include <stdio.h>   /* printf(): para debug */
#endif



/*
 * CONSTANTES 
 */

/*------------------------------------------------------------*/
/* 
 * FunÃ§Ãµes administrativas
 */
 BinarySearchST resize(BinarySearchST st, int factor, size_t nKey, size_t nVal);

/*----------------------------------------------------------*/
/* 
 * Estrutura BÃ¡sica da Tabela de SÃ­mbolos: 
 * 
 * implementaÃ§Ã£o com vetores ordenados
 */
struct binarySearchST {
    
    int n; /* guarda o tamanho */
    int n_keys; /* guarda a quantidade de chaves armazenadas*/
    int current; /* util pro "iterador"*/
    void **keys; /* Guarda uma string*/
    void **values; /* Guarda o comprimento da string + 1*/
    int (*compar)();
    /* size_t *size_keys; */
    size_t *size_values; /*guarda quantos bytes ocupa o dado*/
    
};

/*-----------------------------------------------------------*/
/*
 *  initST(COMPAR)
 *
 *  RECEBE uma funÃ§Ã£o COMPAR() para comparar chaves.
 *  RETORNA (referÃªncia/ponteiro para) uma tabela de sÃ­mbolos vazia.
 *
 *  Ã‰ esperado que COMPAR() tenha o seguinte comportamento:
 *
 *      COMPAR(key1, key2) retorna um inteiro < 0 se key1 <  key2
 *      COMPAR(key1, key2) retorna 0              se key1 == key2
 *      COMPAR(key1, key2) retorna um inteiro > 0 se key1 >  key2
 * 
 *  TODAS OS OPERAÃ‡Ã•ES da ST criada utilizam a COMPAR() para comparar
 *  chaves.
 * 
 */
BinarySearchST
initST(int (*compar)(const void *key1, const void *key2))  {
    
    BinarySearchST ST;
    ST = malloc(sizeof(struct binarySearchST));

    ST->n = 1;
    ST->n_keys = 0;
    ST->current = 0;

    ST->keys = malloc(ST->n * sizeof(void *));
    ST->values = malloc(ST->n * sizeof(void *));
    ST->size_values = calloc(ST->n, sizeof(size_t));
    
    ST->compar = compar;
    return ST;
}

/*-----------------------------------------------------------*/
/*
 *  freeST(ST)
 *
 *  RECEBE uma BinarySearchST  ST e devolve ao sistema toda a memoria 
 *  utilizada por ST.
 *
 */
void freeST(BinarySearchST st) {
    
    int i;

    for (i = 0; i < st->n; i++) {
        free(st->keys[i]);
        free(st->values[i]);
    }

    free(st->keys);
    free(st->values);
    free(st->size_values);
    free(st);
}    

/*------------------------------------------------------------*/
/*
 * OPERAÃ‡Ã•ES USUAIS: put(), get(), contains(), delete(),
 * size() e isEmpty().
 */

/*-----------------------------------------------------------*/
/*
 *  put(ST, KEY, NKEY, VAL, NVAL)
 * 
 *  RECEBE a tabela de sÃ­mbolos ST e um par KEY-VAL e procura a KEY na ST.
 *
 *     - se VAL Ã© NULL, a entrada da chave KEY Ã© removida da ST  
 *  
 *     - se KEY nao e' encontrada: o par KEY-VAL Ã© inserido na ST
 *
 *     - se KEY e' encontra: o valor correspondente Ã© atualizado
 *
 *  NKEY Ã© o nÃºmero de bytes de KEY e NVAL Ã© o nÃºmero de bytes de NVAL.
 *
 *  Para criar uma copia/clone de KEY Ã© usado o seu nÃºmero de bytes NKEY.
 *  Para criar uma copia/clode de VAL Ã© usado o seu nÃºmero de bytes NVAL.
 *
 */
void put(BinarySearchST st, const void *key, size_t nKey, const void *val, size_t nVal) {


        int i, j;
        if (val == NULL) {
            delete(st, key);
            return;
        }

        if (st->n_keys == st-> n) {
            st = resize(st, 2, nKey, nVal);
        }

        i = rank(st, key);

        /* key is already in table*/
        if (i < st->n_keys && st->compar(st->keys[i], key) == 0) {

            st->values[i] = malloc(nVal);
            memcpy(st->values[i], val, nVal);
            return;
        }


        /* insert new key-value pair*/
        /*if (n == keys.length) resize(2*keys.length); resize? */

        for (j = st->n_keys; j > i; j--)  { /* checar se j cmeça com j-1*/

            free(st->keys[j]);
            st->keys[j] = malloc(st->size_values[j-1]);
            memcpy(st->keys[j], st->keys[j-1], st->size_values[j-1]);
            
            free(st->values[j]);
            st->values[j] = malloc(st->size_values[j-1]);
            memcpy(st->values[j], st->values[j-1], st->size_values[j-1]);
            /*st->keys[j] = st->keys[j-1];
            st->values[j] = st->values[j-1];*/
        }


        st->keys[i] = malloc(nKey);
        memcpy(st->keys[i], key, nKey);

        st->values[i] = malloc(nVal);
        memcpy(st->values[i], val, nVal);

        st->size_values[i] = nVal;
        st->n_keys++;

}    

/*-----------------------------------------------------------*/
/*
 *  get(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 *
 *     - se KEY estÃ¡ em ST, RETORNA NULL;
 *
 *     - se KEY nÃ£o estÃ¡ em ST, RETORNA uma cÃ³pia/clone do valor
 *       associado a KEY.
 * 
 */
void *get(BinarySearchST st, const void *key) {

    int i;
    void* cpy;  
    i = rank(st, key); 
    if (i < st->n_keys && st->compar(st->keys[i], key) == 0) {
        cpy = malloc(st->size_values[i]);
        memcpy(cpy, st->values[i], st->size_values[i]);
        return cpy;
    } 

    return NULL;
}

/*-----------------------------------------------------------*/
/* 
 *  CONTAINS(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 * 
 *  RETORNA TRUE se KEY estÃ¡ na ST e FALSE em caso contrÃ¡rio.
 *
 */
Bool
contains(BinarySearchST st, const void *key) {
    
    if (get(st, key) == NULL)
        return FALSE;
    else
        return TRUE;
}

/*-----------------------------------------------------------*/
/* 
 *  DELETE(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 * 
 *  Se KEY estÃ¡ em ST, remove a entrada correspondente a KEY.
 *  Se KEY nÃ£o estÃ¡ em ST, faz nada.
 *
 */
void
delete(BinarySearchST st, const void *key) {
    
    int i, j;
    if (!isEmpty(st) && contains(st, key) == TRUE){
        printf("Nao ta vazio!\n");
        /* compute rank*/
        i = rank(st, key);
        printf("Vou deletar %s\n", (String)st->keys[i]);

        /* key not in table*/
        if (i == st->n_keys || st->compar(st->keys[i], key)!= 0) {
            return;
        }
        

        for (j = i; j < st->n_keys-1; j++)  {            

            free(st->keys[j]);
            st->keys[j] = malloc(st->size_values[j+1]);
            memcpy(st->keys[j], st->keys[j+1], st->size_values[j+1]);
            
            free(st->values[j]);
            st->values[j] = malloc(st->size_values[j+1]);
            memcpy(st->values[j], st->values[j+1], st->size_values[j+1]);
        }

        st->n_keys--;

        /* resize if 1/4 full*/
        /*if (n > 0 && n == keyslength/4) resize(keyasdslength/2);*/

    }


}

int
size(BinarySearchST st)
{
    return st->n_keys;
}

/*-----------------------------------------------------------*/
/* 
 *  ISEMPTY(ST, KEY)
 *
 *  RECEBE uma tabela de sÃ­mbolos ST.
 * 
 *  RETORNA TRUE se ST estÃ¡ vazia e FALSE em caso contrÃ¡rio.
 *
 */
Bool
isEmpty(BinarySearchST st)
{
    return st->n_keys == 0;
}


/*------------------------------------------------------------*/
/*
 * OPERAÃ‡Ã•ES PARA TABELAS DE SÃMBOLOS ORDENADAS: 
 * min(), max(), rank(), select(), deleteMin() e deleteMax().
 */

/*-----------------------------------------------------------*/
/*
 *  MIN(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e RETORNA uma cÃ³pia/clone
 *  da menor chave na tabela.
 *
 *  Se ST estÃ¡ vazia RETORNA NULL.
 *
 */
void *
min(BinarySearchST st) {
    if (isEmpty(st))
        return NULL;

    else {
        void* cpy;
        size_t sze_data = st->size_values[0];

        cpy = malloc(sze_data);
        memcpy(cpy, st->values[0], sze_data);

        return cpy;
    }
}

/*-----------------------------------------------------------*/
/*
 *  MAX(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e RETORNA uma cÃ³pia/clone
 *  da maior chave na tabela.
 *
 *  Se ST estÃ¡ vazia RETORNA NULL.
 *
 */
void *
max(BinarySearchST st)
{
    if (isEmpty(st))
        return NULL;
    else {
        void* cpy;
        size_t sze_data = sizeof(st->size_values[st->n_keys-1]);

        cpy = malloc(sze_data);
        memcpy(cpy, st->values[st->n_keys-1], sze_data);
        
        return cpy;
    }
}

/*-----------------------------------------------------------*/
/*
 *  RANK(ST, KEY)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e uma chave KEY.
 *  RETORNA o nÃºmero de chaves em ST menores que KEY.
 *
 *  Se ST estÃ¡ vazia RETORNA NULL.
 *
 */
int
rank(BinarySearchST st, const void *key) {
    int lo = 0, hi = st->n_keys-1; 
    while (lo <= hi) { 

        int mid = lo + ((hi - lo) / 2); 
        int cmp = st->compar(key, st->keys[mid]);
        
        if (cmp < 0) 
            hi = mid - 1; 

        else if (cmp > 0) 
            lo = mid + 1; 

        else 
            return mid; 

    }
    if (isEmpty(st))
        return 0;
    return lo;
}

/*-----------------------------------------------------------*/
/*
 *  SELECT(ST, K)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e um inteiro K >= 0.
 *  RETORNA a (K+1)-Ã©sima menor chave da tabela ST.
 *
 *  Se ST nÃ£o tem K+1 elementos RETORNA NULL.
 *
 */
void *
select(BinarySearchST st, int k) {
    if (k+1 < st->n_keys)
        return st->keys[k+1];
    else
        return NULL;
}

/*-----------------------------------------------------------*/
/*
 *  deleteMIN(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e remove a entrada correspondente
 *  Ã  menor chave.
 *
 *  Se ST estÃ¡ vazia, faz nada.
 *
 */
void
deleteMin(BinarySearchST st) {
    if (!isEmpty(st)) {
        delete(st, st->values[0]);
    }
        
}

/*-----------------------------------------------------------*/
/*
 *  deleteMAX(ST)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e remove a entrada correspondente
 *  Ã  maior chave.
 *
 *  Se ST estÃ¡ vazia, faz nada.
 *
 */
void
deleteMax(BinarySearchST st){
    if (!isEmpty(st)){
        delete(st, st->values[st->n_keys-1]);
    }
}

/*-----------------------------------------------------------*/
/* 
 *  KEYS(ST, INIT)
 * 
 *  RECEBE uma tabela de sÃ­mbolos ST e um Bool INIT.
 *
 *  Se INIT Ã© TRUE, KEYS() RETORNA uma cÃ³pia/clone da menor chave na ST.
 *  Se INIT Ã© FALSE, KEYS() RETORNA a chave sucessora da Ãºltima chave retornada.
 *  Se ST estÃ¡ vazia ou nÃ£o hÃ¡ sucessora da Ãºltima chave retornada, KEYS() RETORNA NULL.
 *
 *  Se entre duas chamadas de KEYS() a ST Ã© alterada, o comportamento Ã© 
 *  indefinido. 
 *  
 */
void * 
keys(BinarySearchST st, Bool init)
{
    void* cpy;
    size_t size_data = st->size_values[0];

    cpy = malloc(size_data);

    if (st->current + 1 >= st->n_keys) {
        return NULL;
    }
    if (init == TRUE) {
        memcpy(cpy, st->keys[0], size_data);
    }

    else {
        memcpy(cpy, st->keys[++st->current], size_data);
    }

    return cpy;
}

/*-----------------------------------------------------------*/
/*
  Visit each entry on the ST.

  The VISIT function is called, in-order, with each pair key-value in the ST.
  If the VISIT function returns zero, then the iteration stops.

  visitST returns zero if the iteration was stopped by the visit function,
  nonzero otherwise.
*/
int
visitST(BinarySearchST st, int (*visit)(const void *key, const void *val))
{
    return EXIT_SUCCESS;

}
    

/*------------------------------------------------------------*/
/* 
 * FunÃ§Ãµes administrativas*/
 BinarySearchST resize(BinarySearchST st, int factor, size_t nKey, size_t nVal) {
    
    void **new_keys;
    void **new_values;
    size_t *new_size_values;
    /*size_t *new_size_values;*/

    int i, oldsize;

    new_keys = malloc(st->n * sizeof(void *));
    new_values = malloc(st->n * sizeof(void *));
    new_size_values = malloc(st->n * sizeof(size_t));
    /*new_size_values = malloc(st->n * sizeof(size_t));*/

    for(i = 0; i < st->n ; i++) {
        
        new_keys[i] = malloc(nKey);
        memcpy(new_keys[i], st->keys[i], nKey);

        new_values[i] = malloc(nVal);
        memcpy(new_values[i], st->values[i], nVal);

        new_size_values[i] = st->size_values[i];

        /*memcpy(new_size_values[i], st->size_values[i], sizeof(size_value[i]));*/
        
        free(st->keys[i]);
        free(st->values[i]);

    }
    free(st->keys);
    free(st->values);
    free(st->size_values);

    oldsize = st->n;
    st->n = factor * st->n;

    st->keys = malloc(st->n * sizeof(void *));
    st->values = malloc(st->n * sizeof(void *));
    st->size_values = malloc(st->n * sizeof(size_t));

    for (i = 0; i < oldsize; i++) {
        st->keys[i] = malloc(nKey);
        memcpy(st->keys[i], new_keys[i], nKey);

        st->values[i] = malloc(nVal);
        memcpy(st->values[i], new_values[i], nVal);

        st->size_values[i] = new_size_values[i];

        free(new_keys[i]);
        free(new_values[i]);

    }

    free(new_keys);
    free(new_values);
    free(new_size_values);


    return st;
}
 /**/
