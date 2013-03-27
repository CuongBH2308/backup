package wb;

import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;

public class WeiboDB {

	private String _database;
	
	Connection _connection;
	
	private PreparedStatement _stmtInsertWeibo;
	private PreparedStatement _stmtInsertComment;

	public WeiboDB(final String database) throws Exception {
		_database = database;

		// load jdbc for sqlite
		Class.forName("org.sqlite.JDBC");

		
		// create a database connection
		final String conn = "jdbc:sqlite:" + _database;
		_connection = DriverManager.getConnection(conn);
		
		// Initialize database
		Statement statement = _connection.createStatement();
		statement.setQueryTimeout(30); // set timeout to 30 sec.

		statement.executeUpdate("drop table if exists timeline");
		statement
				.executeUpdate("create table timeline (wbid integer primary key, time Date, text string, image blob, rid integer)");
		
		statement.executeUpdate("drop table if exists comments");
		statement
				.executeUpdate("create table comments (cid integer primary key, wbid integer, time Date, text string)");
		
		statement.close();
		
		_stmtInsertWeibo = _connection.prepareStatement("insert into timeline values(?, ?, ?, ?, ?)");
		_stmtInsertComment = _connection.prepareStatement("insert into comments values(?, ?, ?, ?)");
	}
	
	public void close() throws SQLException
	{
		_connection.close();
	}

	public void insertWeibo(final Long wbid, final Date time,
			final String text, final byte[] image, final Long rid) throws Exception{

		_stmtInsertWeibo.setLong(1, wbid);
		_stmtInsertWeibo.setDate(2, time);
		_stmtInsertWeibo.setString(3, text);
		_stmtInsertWeibo.setBytes(4, image);
		_stmtInsertWeibo.setLong(5, rid);
		
		_stmtInsertWeibo.execute();
		
	}

	public void insertComment(final Long cid, final Long wbid, final Date time,
			final String text) throws Exception{

		_stmtInsertComment.setLong(1, cid);
		_stmtInsertComment.setLong(2, wbid);
		_stmtInsertComment.setDate(3, time);
		_stmtInsertComment.setString(4, text);
		
		_stmtInsertComment.execute();
		
	}

}
