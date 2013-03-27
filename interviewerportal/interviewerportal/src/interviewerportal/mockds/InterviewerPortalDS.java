package interviewerportal.mockds;

import interviewerportal.domain.Question;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.springframework.stereotype.Component;

import edu.umd.cs.findbugs.annotations.CheckForNull;

@Component
public class InterviewerPortalDS {
    private Map<Long, Question> allQuestions = new HashMap<Long, Question>();

    public InterviewerPortalDS() {

        for (long i = 0; i < allQuestions.size(); i++) {
            allQuestions.put(i, createQuestion(i));
        }

    }

    public final Set<Long> getAllQuestionIds() {
        return allQuestions.keySet();

    }

    @CheckForNull
    public final Question getQuestion(final long qid) {
        return allQuestions.get(qid);
    }

    private Question createQuestion(final long questionId) {
        Question q = new Question(questionId, String.format("Question %d",
                questionId), String.format("Answer %d", questionId));

        Map<String, String> followupQAs = new LinkedHashMap<String, String>();
        final int count = 4;
        for (int i = 1; i < count; i++) {
            followupQAs.put(
                    String.format("Followup Question %d.%d", questionId, i),
                    String.format("Followup Answer %d.%d", questionId, i));
        }
        q.setFollowupQAs(followupQAs);

        q.setObjective(String.format("Objective %d", questionId));
        q.setPhoneSuitable(questionId % 2 == 0);
        q.setCategory("C++");

        Set<String> tags = new HashSet<String>();
        tags.add("C++");
        tags.add("algorithm");
        tags.add("backend");
        q.setTags(tags);

        q.setUserId(questionId);

        q.setAddedTime(System.currentTimeMillis());

        Set<String> fromFirms = new HashSet<String>();
        fromFirms.add("MorganStanley");
        fromFirms.add("Autodesk");
        q.setFromFirms(fromFirms);

        return q;
    }

    public final List<Question> getAllQuestions() {
        return new ArrayList<Question>(allQuestions.values());
    }
}
