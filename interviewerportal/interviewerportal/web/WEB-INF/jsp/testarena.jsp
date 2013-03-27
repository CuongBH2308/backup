<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<%@ page import="java.util.*"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Interviewer Portal Test Arena</title>
</head>
<body>
	<a href="/questions/1">Question1 1</a>
	<br /> Hello! The time is now
	<%=new java.util.Date()%>
	<br />
	<%
		System.out.println("Get Date");
		Date date = new java.util.Date();
		out.println(date);
	%>
	<br /> The current time is
	<%=date%>

	<%
		out.println("Your machine's IP is:");
		out.println(request.getRemoteAddr());
	%>
	<br />
	<table border=2>
		<%
			for (int i = 0; i < 10; i++) {
		%>
		<tr>
			<td>number</td>
			<td><%=i + 1%></td>
		</tr>
		<%
			}
		%>
	</table>

	<table border=2>
		<c:forEach var="qid" items="${qIdList}">
			<tr>
				<td>${qid}</td>
			</tr>
		</c:forEach>
	</table>

</body>
</html>