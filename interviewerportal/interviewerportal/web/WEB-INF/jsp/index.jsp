<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Interviewer Portal</title>
<%@ include file="components/header.jsp"%>
</head>

<body>
	<%@ include file="components/topbar.jsp"%>
	<div class="container-fluid">
		<div class="row-fluid">
			<%@ include file="components/sidebar.jsp"%>
			<!--/span-->
			<div class="span9">
				<div align="center">
					<img src="/interviewerportal/img/interviewer.jpg" height="50%" width="50%"/>
				</div>
				<br/> 
				<br/>
				<div align="center">
					<input class="span8" type="text" data-provide="typeahead"> <input class="btn" type="submit" value="Search">
				</div>
				<br/> 
				<br/>
				<div align="center">
					tag cloud
				</div>
			</div>
		</div>
	</div>
</body>
</html>