package interviewerportal.dao;

import interviewerportal.domain.Question;

import java.util.List;
import java.util.Set;

public interface QuestionDao {
    Question getQuestion(long questionId);

    Set<Long> getAllQuestionIds();

    List<Question> getAllQuestions();
}
