package cc4102.tarea3.olguin_romero;

/**
 * Created by arachnid92 on 29-11-15.
 */
public interface Node {
    boolean put(String key, String value);
    String get(String key);
    boolean delete(String key);
}
