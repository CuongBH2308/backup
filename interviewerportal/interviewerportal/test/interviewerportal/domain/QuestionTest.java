package interviewerportal.domain;

import junit.framework.Assert;

import org.junit.Test;

public class QuestionTest {

    @Test
    public final void test() {
        Question q = new Question(1, "What is your name?", "I am lzprgmr");
        Assert.assertEquals(1, q.getQuestionId());
        Assert.assertEquals("What is your name?", q.getQuestion());
        Assert.assertEquals("I am lzprgmr", q.getExpectedAnswer());
    }

}
