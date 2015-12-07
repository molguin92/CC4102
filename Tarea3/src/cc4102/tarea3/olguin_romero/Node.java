package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public abstract class Node {

    public Node left;
    public Node right;
    public String value;
    public String key;

    abstract Node put(String key, String value);
    abstract String get(String key);
    abstract Node delete(String key);
}
