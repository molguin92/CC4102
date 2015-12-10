package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 09-12-15.
 */
public interface INode {
    Node put(int key, String value);
    String get(int key);
    Node delete(int key);
}
