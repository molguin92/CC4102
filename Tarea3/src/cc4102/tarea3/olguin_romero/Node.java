package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public abstract class Node implements INode {

    public Node left;
    public Node right;
    public String value;
    public int key;

    public abstract Node put(int key, String value);
    public abstract String get(int key);
    public abstract Node delete(int key);
}
