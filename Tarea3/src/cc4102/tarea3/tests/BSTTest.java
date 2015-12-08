package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.BinarySearchTree;
import org.junit.Before;

/**
 * Created by arachnid92 on 06-12-15.
 */
public class BSTTest extends TreeTest {

    @Before
    public void setUp() throws Exception {
        tree = new BinarySearchTree();
        populate();
    }
}