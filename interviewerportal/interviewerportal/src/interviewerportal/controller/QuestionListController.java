package interviewerportal.controller;

import interviewerportal.service.QuestionService;

import java.util.Map;

import javax.annotation.Resource;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class QuestionListController {

    private static final Logger LOGGER = LoggerFactory
            .getLogger(QuestionListController.class);
    @Resource
    private QuestionService questionService;

    @RequestMapping(method = RequestMethod.GET, value = "/questions/{tag}")
    public final ModelAndView getQuestion(@PathVariable final String tag) {
        Map<String, Object> model = questionService.getAllQuestionsModel();
        if (model != null) {
            return new ModelAndView("question", model);
        } else {
            LOGGER.info("Well, it is null, I am sorry");
            return new ModelAndView("noresource", "resource", String.format(
                    "/questions/%s", tag));
        }
    }

}
