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



    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:

****************************************************************/

/******************************************************************************
 *  Compilation:  javac-algs4 Combinacao.java
 *  Execution:    java Combinacao n k [opcao]
 *  
 *  Enumera todas as combinações dos números em {1,2,...,n} k a k.
 *  Se opcao = 0 (defaul), gera e exibe todas as permutações em ordem 
 *  lexicográfica
 *  Se opcao = 1 apenas, __gera todas__ as combinações, mas __não__ as 
 *  exibe; apenas exibe o total de combinações.
 *
 * % java Combinacao 5 3 1
 * 10
 * elapsed time = 0.002
 * % java Combinacao 5 3 
 * 1 2 3 
 * 1 2 4 
 * 1 2 5 
 * 1 3 4 
 * 1 3 5 
 * 1 4 5 
 * 2 3 4 
 * 2 3 5 
 * 2 4 5 
 * 3 4 5 
 * 10
 * elapsed time = 0.002
 * % java Combinacao 100 3 1
 * 161700
 * elapsed time = 0.004
 * % java Combinacao 1000 3 1
 * 166167000
 * elapsed time = 0.726
 *   
 ******************************************************************************/

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Stopwatch;

//TODO : rever quais variáveis são publicas e quais não sao

public class Combinacao {
    private static int count = 0; // contador de combinações
    private static int opcao = 0; 
        // 1 imprimir apenas o número de combinações (default)
        // 0 imprimir as combinações e o número de combinações

    public static void combinacao(int n, int k) {
        
        if (k < 0 || n < 0) {
            throw new IllegalArgumentException("Por favor, digite valores não negativos de n e k...\n");
        }

        int seq[] = new int[k];
        boolean finished = false;
            // Variavel booleana que determina o fim dos cálculos de combinacaoo(n,k).

        int pivo = k-1;
            // Variável que guarda a casa do vetor seq[] sendo analisada.
        int max = n;
            // Guarda o valor máximo que cada casa do vetor seq[] pode ter. A função NovoMAximo() retorna o valor maximo para a casa de seq[] indicada por pivo.
        int novoPivo;
            // Armazena um valor de pivo para modifica-lo sem perder a referencia ao valor original.
        int aux;
            // Armazena o valor de seq[pivo] sem perder o valor original do array.

        if (n == 0 || k == 0) {
            finished = true;
        }

        inicializaVetor(seq, k);

        while(!finished) {

            imprimeCombinacao(seq, k, opcao);   
            if(seq[pivo] < max) {
                seq[pivo]++;
            }

            else { //backtracking
                while(pivo > 0 && seq[pivo] >= max) {
                    pivo--;
                    max = novoMaximo(n, k, pivo);
                }

                if (pivo == 0 && seq[pivo] == max) {
                    finished = true;
                }
                aux = seq[pivo];
                novoPivo = pivo; 
                while (novoPivo < k) {
                    seq[novoPivo] = ++aux;
                    novoPivo++;
                }
                pivo = k-1;
            }

            max = novoMaximo(n, k, pivo);
            count++;
        }
    }

    private static int novoMaximo(int n, int k, int pivo) {
        return ( n-k+(pivo+1) );
    }

    private static void inicializaVetor(int[] seq, int tamanho) {
        for(int i = 0; i < tamanho; i++) {
            seq[i] = i+1;
        }
    }

    private static void imprimeCombinacao(int[] seq, int tamanho, int opcao) { // eu acho mais legal se ele não colocar uma virgula no pivo
        if (opcao == 0)
            imprimeVetor(seq, tamanho);
    }

    private static void imprimeVetor(int[] v, int tamanho) {
        for (int item : v) {
            StdOut.print(item + " ");
        }
        StdOut.print('\n');
    }

    // private static int numCombs (int n, int k) {
    // TODO : Eu posso simplesmente remover o calculo do ncombs, e fazer todas combinações, depois contabilizar...

    // }

    
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int k = Integer.parseInt(args[1]);
        if (args.length == 3) {
            opcao = Integer.parseInt(args[2]);
        }
        Stopwatch timer = new Stopwatch();
        combinacao(n, k);
        StdOut.println(count);
        StdOut.println("elapsed time = " + timer.elapsedTime());
    }
}
