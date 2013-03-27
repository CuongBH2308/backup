package interviewerportal.controller;

import interviewerportal.service.QuestionService;

import javax.annotation.Resource;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class HomePageController {
    @Resource
    private QuestionService questionService;

    private static final Logger LOGGER = LoggerFactory
            .getLogger(HomePageController.class);

    @RequestMapping(method = RequestMethod.GET, value = "/*")
    public final ModelAndView goHome() {
        LOGGER.info("HomePage request");

        return new ModelAndView("index");

    }

}
