package interviewerportal.dao.mockds;

import interviewerportal.dao.QuestionDao;
import interviewerportal.domain.Question;
import interviewerportal.mockds.InterviewerPortalDS;

import java.util.List;
import java.util.Set;

import javax.annotation.Resource;

import org.springframework.stereotype.Component;

import edu.umd.cs.findbugs.annotations.CheckForNull;
import edu.umd.cs.findbugs.annotations.NonNull;

@Component
public class MockDSQuestionDao implements QuestionDao {

    @Resource(name = "interviewerPortalDS")
    private InterviewerPortalDS dataSource;

    @CheckForNull
    public final Question getQuestion(final long questionId) {
        return dataSource.getQuestion(questionId);
    }

    @NonNull
    public final Set<Long> getAllQuestionIds() {
        return dataSource.getAllQuestionIds();

    }

    @CheckForNull
    public final List<Question> getAllQuestions() {
        return dataSource.getAllQuestions();
    }

}
