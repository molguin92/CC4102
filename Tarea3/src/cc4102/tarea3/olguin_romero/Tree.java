package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public interface Tree {
    void put(String key, String value);
    String get(String key);
    String delete (String key);
    int size();
}
