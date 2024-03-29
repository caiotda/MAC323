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

// Performance : Toda operação do deck deve ter tempo de execução constante
// Memória : O deck com n itens deve ocupar no máximo 48n+192 bytes
// iterador : Toda operação deve rodar em tempo constante


import java.lang.IllegalArgumentException;
import java.lang.UnsupportedOperationException;
import java.util.NoSuchElementException;

import java.util.Iterator;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class Deque<Item> implements Iterable<Item> {

    private class node<Item> {

        private Item item;
        private node<Item> next;
        private node<Item> prev;

        public node(Item content, node<Item> next, node<Item> prev) {
            this.item = content;
            this.next = next;
            this.prev = prev;
        }
    }
    private node<Item> first;
    private node<Item> last;
    private int n;

    // construct an empty deque
    public Deque() {
        n = 0;
        first = null;
        last = null;
    }

    // is the deque empty?
    public boolean isEmpty() {
        return n == 0;
    }

    // return the number of items on the deque
    public int size() {
        return n;
    }

    // add the item to the front
    public void addFirst(Item item) {

        if (item == null) {
            throw new IllegalArgumentException();
        }

        node<Item> newContent = new node<Item>(item, first, null);
        if (n == 0)
            last = newContent;
        else
            first.prev = newContent;
        first = newContent;
        n++;
        if (first == null) {
            StdOut.println("Da problea quando n vale " + n);
        }
    }

    // add the item to the back
    public void addLast(Item item) {

        if (item == null) {
            throw new IllegalArgumentException();
        }

        node<Item> newContent = new node<Item>(item, null, last);
        if (n == 0)
            first = newContent;
        else
            last.next = newContent;
        last = newContent;
        n++;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        
        if (n == 0)
            throw new NoSuchElementException();

        Item content = first.item;
        first = first.next;
        n--;
        return content;
    }

    // remove and return the item from the back
    public Item removeLast() {

        if (n == 0)
            throw new NoSuchElementException();

        Item content = last.item;
        last = last.prev;
        n--;
        return content;

    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new DoubleListIterator(first);
    }

    private class DoubleListIterator implements Iterator<Item> {
        private node<Item> current;
        public DoubleListIterator(node<Item> start) {
            current = start;
        }
        public Item next() {

        if (!hasNext())
            throw new NoSuchElementException();

            Item currentItem = current.item;
            current = current.next;
            return currentItem;
        }

        public boolean hasNext() {
            return current != null;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

    }
    // unit testing (required)
    public static void main(String[] args) {
        Deque <Character> deque = new Deque<Character>();
        StdOut.println("O Deque está vazio? " + deque.isEmpty());
        
        
//---------------------------TESTE DA INSERÇÃO NO FIM-------------------------//
        while (StdIn.hasNextChar()) {
            char dequeChar = StdIn.readChar();
            if (dequeChar != ' ') {
                StdOut.println("-------Tamanho do Deque : " + deque.size()+"----");
                // StdOut.println("Inserindo no início o caracter " + dequeChar);
                // deque.addFirst(dequeChar);
                StdOut.println("Inserindo no fim o caracter " + dequeChar);
                deque.addLast(dequeChar);
            }
        }
//----------------------------------------------------------------------------//

//------------------------TESTE DO ITERADOR-----------------------------------//
        char letras[] = new char[deque.n];
        int count = 0;

        for(char atual : deque) { // o iterador ta pulando o primeiro item
            letras[count] = atual;
            StdOut.println("Item atual : " + atual);
            count++;
        }

        boolean finished;

        finished = count == deque.n;
        StdOut.println("Imprimi todos os itens? " + finished);
//----------------------------------------------------------------------------//

//--------------------TESTE DA REMOÇÃO NO INÍCIO------------------------------//
        while (!deque.isEmpty()) {
                StdOut.println("----Tamanho do Deque : " + deque.size()+"----");
                StdOut.println("Deletando do inicio...");
                deque.removeFirst();
        }
//----------------------------------------------------------------------------//

//---------------------TESTE DA INSERÇÃO NO INÍCIO----------------------------//
        for (char atual : letras) {
            StdOut.println("Inserindo no início o caracter " + atual);
            deque.addFirst(atual);
        }
//----------------------------------------------------------------------------//

//--------------------TESTE DA REMOÇÃO NO FIM---------------------------------//
        while (!deque.isEmpty()) {
                StdOut.println("----Tamanho do Deque : " + deque.size()+"----");
                StdOut.println("Deletando do fim...");
                deque.removeLast();
        }
//------------------------------------------------------------------------------
        StdOut.println("Imprimi " + count + " itens e meu deck tem tamanho " + deque.n);
        StdOut.println("O Deque está vazio? " + deque.isEmpty());

    }

}