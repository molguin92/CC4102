package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public abstract class Node {

    public Node left;
    public Node right;
    public String value;
    public int key;

    abstract Node put(int key, String value);
    abstract String get(int key);
    abstract Node delete(int key);
}
