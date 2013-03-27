package interviewerportal.controller;

import interviewerportal.service.QuestionService;

import java.util.Map;

import javax.annotation.Resource;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class TestArenaController {
    @Resource
    private QuestionService questionService;

    private static final Logger LOGGER = LoggerFactory
            .getLogger(TestArenaController.class);

    @RequestMapping(method = RequestMethod.GET, value = "/testarena")
    public final ModelAndView goHome() {
        LOGGER.info("TestArea request");

        Map<String, Object> model = questionService.getAllQuestionIdsModel();
        if (model != null) {
            return new ModelAndView("testarena", model);
        } else {
            LOGGER.info("Well, it is null, I am sorry");
            return new ModelAndView("noresource", "resource", "/testarena");
        }
    }
}
