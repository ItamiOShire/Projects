import java.util.EmptyStackException;

interface StackInterface<T> {
    void push(T element) throws NullPointerException;
    T pop();
    T peek();
    boolean isEmpty();
}

class Stack<T> implements StackInterface<T> {
    private Node<T> top;
    private int size;

    private static class Node<T> {
        T data;
        Node<T> next;

        Node(T data) {
            this.data = data;
        }
    }

    @Override
    public void push(T element) {
        Node<T> newNode = new Node<>(element);
        newNode.next = top;
        top = newNode;
        size++;
    }

    @Override
    public T pop() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        T data = top.data;
        top = top.next;
        size--;
        return data;
    }

    @Override
    public T peek() {
        if (isEmpty()) {
            throw new EmptyStackException();
        }
        return top.data;
    }

    @Override
    public boolean isEmpty() {
        return top == null;
    }

    public int size() {
        return size;
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder("[");
        Node<T> current = top;
        while (current != null) {
            result.append(current.data);
            if (current.next != null) {
                result.append(", ");
            }
            current = current.next;
        }
        result.append("]");
        return result.toString();
    }
}
public class Main {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Brak argumentu wejściowego.");
            return;
        }

        String inputExpression = args[0];

        try {
            String result = translate(inputExpression.split(""));
            System.out.println("Wynik: " + result);
        } catch (IllegalArgumentException e) {
            System.out.println("BLAD DANYCH WEJSCIOWYCH! " + e.getMessage());
        }
    }

    public static String translate(String[] tokens) {
        Stack<String> stack = new Stack<>();

        for (String token : tokens) {
            if (token.matches("[a-zA-Z]")) {
                stack.push(token);
            } else if (token.matches("[+\\-*/]")) {
                if (stack.size() < 2) {
                    throw new IllegalArgumentException("Na stosie jest za malo elementow, zeby wykonac operacje!");
                }
                String operand2 = stack.pop();
                String operand1 = stack.pop();
                String result = "(" + operand1 + token + operand2 + ")";
                stack.push(result);
            } else {
                throw new IllegalArgumentException("Bledny operator: " + token);
            }
        }

        if (stack.size() != 1) {
            throw new IllegalArgumentException("Koniec algorytmu, a stos nie jest pusty: " + stack);
        }

        return stack.pop();
    }
}
