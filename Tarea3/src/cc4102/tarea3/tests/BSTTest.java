package cc4102.tarea3.tests;

import cc4102.tarea3.olguin_romero.BinarySearchTree;
import cc4102.tarea3.olguin_romero.Node;
import org.junit.After;
import org.junit.Before;

import static org.junit.Assert.assertEquals;

/**
 * Created by arachnid92 on 06-12-15.
 */
public class BSTTest extends TreeTest {

    @Before
    public void setUp() throws Exception {
        tree = new BinarySearchTree();
        populate();
    }

    @After
    public void tearDown() throws Exception {
        assertIsBST();
    }

    @Override
    public void testDelete() throws Exception {
        assertEquals(initsize, tree.size());

        for(int i = 0; i < initsize; i++)
        {
            tree.delete(i);
            assertEquals(initsize - i - 1, tree.size());
            assertEquals(null, tree.get(i));
            assertIsBST();
        }
    }

    void assertIsBST()
    {
        Node root = tree.getRoot();
        recursiveCheckBSTNode(root);
    }

    void recursiveCheckBSTNode(Node node)
    {
        if((node == null) || (node.left != null && node.left.key < node.key) || (node.right != null && node.right.key < node.key))
            return;
        else
            throw new AssertionError("Not BST.");
    }
}