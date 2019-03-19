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

import java.lang.Math;
import java.lang.IllegalArgumentException;

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.Stopwatch;

public class PercolationStats {
    
    private double[] allTrials;
    private double sqrtTrials;
    private int trials;
    private int percolationIndex; // mudar esse nome.
    private double mean;
    private double stdDev;
    private double var;

    // perform independent trials on an n-by-n grid
    public PercolationStats(int n, int trials) {
        // precisa realizar os experimentos independentes tambem.
        this.allTrials = new double[trials];
        this.sqrtTrials = Math.sqrt(trials);
        this.trials = trials;

        for (int i = 0; i < this.trials; i++) {
            percolationIndex = makeTrial(n);
            this.allTrials[i] = (double)percolationIndex/(double)(n*n);
        }
        this.mean = StdStats.mean(this.allTrials);
        this.stdDev = StdStats.stddev(this.allTrials);
        this.var = StdStats.var(this.allTrials);
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return this.stdDev;
    }

    // sample mean of percolation threshold
    public double mean() {
        return this.mean;
    }


    // low endpoint of 95% confidence interval
    public double confidenceLow() {
        return (this.mean - (1.96*this.var)/(this.sqrtTrials));
    }

    // high endpoint of 95% confidence interval
    public double confidenceHigh() {
        return (this.mean + (1.96*this.var)/(this.sqrtTrials));

    }

   // test client (see below)
   public static void main(String[] args) {

       Stopwatch timer = new Stopwatch();
       int n = Integer.parseInt(args[0]);
       int t = Integer.parseInt(args[1]);

       PercolationStats statsTest = new PercolationStats(n, t);
       StdOut.println("mean() : " + statsTest.mean());
       StdOut.println("stddev() : " + statsTest.stddev());
       StdOut.println("confidenceLow() : " + statsTest.confidenceLow());
       StdOut.println("confidenceHigh() : " + statsTest.confidenceHigh());
       StdOut.println("Elapsed time : " + timer.elapsedTime());
       
   }
    private int makeTrial(int n) {
        Percolation currentTrial = new Percolation(n);
        int randomRow, randomColumn;

        while(!currentTrial.percolates()) {

            randomRow = StdRandom.uniform(n);
            randomColumn = StdRandom.uniform(n);
            if( !currentTrial.isFull(randomRow, randomColumn)) {
                currentTrial.open(randomRow, randomColumn);
            }

        }

        return currentTrial.numberOfOpenSites();
    }

}