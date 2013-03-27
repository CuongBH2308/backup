package interviewerportal.service;

import interviewerportal.dao.QuestionDao;
import interviewerportal.domain.Question;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.annotation.Resource;

import org.springframework.stereotype.Service;

import edu.umd.cs.findbugs.annotations.CheckForNull;

@Service
public class QuestionService {

    @Resource(name = "mockDSQuestionDao")
    private QuestionDao questionDao;

    @CheckForNull
    public final Map<String, Object> getQuestionModel(final long questionId) {

        Map<String, Object> model = null;
        Question q = questionDao.getQuestion(questionId);
        if (q != null) {
            model = new HashMap<String, Object>();
            model.put("question", q);
        }

        return model;
    }

    public final Map<String, Object> getAllQuestionIdsModel() {
        Map<String, Object> model = null;
        Set<Long> qIds = questionDao.getAllQuestionIds();
        if (qIds != null) {
            model = new HashMap<String, Object>();
            model.put("qIdList", qIds);
        }
        return model;
    }

    public final Map<String, Object> getAllQuestionsModel() {
        Map<String, Object> model = null;
        List<Question> qList = questionDao.getAllQuestions();
        if (qList != null) {
            model = new HashMap<String, Object>();
            model.put("qList", qList);
        }
        return model;
    }

}
