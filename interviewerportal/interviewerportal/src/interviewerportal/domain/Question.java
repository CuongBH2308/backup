package interviewerportal.domain;

import java.util.Map;
import java.util.Set;

public class Question {
    private final long questionId;
    private String question;
    private String expectedAnswer;
    private Map<String, String> followupQAs; // need to keep the sequence
    private String objective;
    private boolean phoneSuitable;
    private String category; // how to define it?
    private Set<String> tags;
    private long userId; // added by
    private long addedTime; // here use long (current millisecond) because the
                            // class Date is mutable, you can then choose
                            // different view class based on this long
    private Map<Long, Long> editedBy; // <userid, editTime>
    private Set<String> fromFirms;

    public Question(final long questionIdArg, final String questionArg,
            final String expectedAnswerArg) {
        this.questionId = questionIdArg;
        this.question = questionArg;
        this.expectedAnswer = expectedAnswerArg;
    }

    public final long getQuestionId() {
        return questionId;
    }

    public final String getQuestion() {
        return question;
    }

    public final void setQuestion(final String questionArg) {
        this.question = questionArg;
    }

    public final String getExpectedAnswer() {
        return expectedAnswer;
    }

    public final void setExpectedAnswer(final String expectedAnswerArg) {
        this.expectedAnswer = expectedAnswerArg;
    }

    public final Map<String, String> getFollowupQAs() {
        return followupQAs;
    }

    public final void setFollowupQAs(final Map<String, String> followupQAsArg) {
        this.followupQAs = followupQAsArg;
    }

    public final String getObjective() {
        return objective;
    }

    public final void setObjective(final String objectiveArg) {
        this.objective = objectiveArg;
    }

    public final boolean isPhoneSuitable() {
        return phoneSuitable;
    }

    public final void setPhoneSuitable(final boolean phoneSuitableArg) {
        this.phoneSuitable = phoneSuitableArg;
    }

    public final String getCategory() {
        return category;
    }

    public final void setCategory(final String categoryArg) {
        this.category = categoryArg;
    }

    public final Set<String> getTags() {
        return tags;
    }

    public final void setTags(final Set<String> tagsArg) {
        this.tags = tagsArg;
    }

    public final long getUserId() {
        return userId;
    }

    public final void setUserId(final long userIdArg) {
        this.userId = userIdArg;
    }

    public final long getAddedTime() {
        return addedTime;
    }

    public final void setAddedTime(final long addedTimeArg) {
        this.addedTime = addedTimeArg;
    }

    public final Map<Long, Long> getEditedBy() {
        return editedBy;
    }

    public final void setEditedBy(final Map<Long, Long> editedByArg) {
        this.editedBy = editedByArg;
    }

    public final Set<String> getFromFirms() {
        return fromFirms;
    }

    public final void setFromFirms(final Set<String> fromFirmsArg) {
        this.fromFirms = fromFirmsArg;
    }

}
