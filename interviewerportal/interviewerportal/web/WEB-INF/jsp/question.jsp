<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
	pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Question Page</title>
<%@ include file="components/header.jsp"%>
</head>
<body>
	<%@ include file="components/topbar.jsp"%>
	<div class="container-fluid">
		<div class="row-fluid">
			<%@ include file="components/sidebar.jsp"%>
			<!--/span-->
			<div class="span9">
				<h1>Question</h1>
				<table class="table table-striped">
					<tbody>
						<tr>
							<td>Question</td>
							<td>${question.question}</td>
						</tr>
						<tr>
							<td>Expected Answer</td>
							<td>${question.expectedAnswer}</td>
						</tr>
					</tbody>
				</table>
			</div>
		</div>
	</div>

</body>
</html>