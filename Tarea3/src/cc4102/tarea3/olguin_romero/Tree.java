package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public interface Tree {
    void put(int key, String value);
    String get(int key);
    void delete (int key);
    int size();
    Node getRoot();
}
