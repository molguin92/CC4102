package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.SplayTree;
import org.junit.Before;

import static org.junit.Assert.*;

/**
 * Created by arachnid92 on 09-12-15.
 */
public class SplayTreeTest extends TreeTest {

    @Before
    public void setUp() throws Exception {
        this.tree = new SplayTree();
        populate();
    }
}