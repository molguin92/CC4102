package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.Node;
import cc4102.tarea3.olguin_romero.SplayTree;

import static org.junit.Assert.assertEquals;

/**
 * Created by arachnid92 on 07-12-15.
 */
public class SplayTest extends TreeTest {

    @Override
    public void setUp() throws Exception {
        tree = new SplayTree();
        populate();
    }

    @org.junit.Test
    @Override
    public void testPut() throws Exception {
        assertEquals(initsize, tree.size());
        tree.put("new key", "new value");
        assertEquals(initsize + 1, tree.size());
        assertIsSplay("new key");
    }

    void assertIsSplay(String key)
    {
        Node root = tree.getRoot();
        int comp = root.key.compareTo(key);
        if (comp != 0) throw new AssertionError("Not SplayTree.");
    }
}