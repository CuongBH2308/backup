package wb;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.sql.Date;
import java.util.List;

import weibo4j.Account;
import weibo4j.Comments;
import weibo4j.Oauth;
import weibo4j.Weibo;
import weibo4j.http.AccessToken;
import weibo4j.model.Comment;
import weibo4j.model.PostParameter;
import weibo4j.model.Status;
import weibo4j.model.WeiboException;
import weibo4j.org.json.JSONObject;
import weibo4j.util.BareBonesBrowserLaunch;
import weibo4j.util.WeiboConfig;


public class WeiboSyncer {

	private Oauth _auth = new Oauth();

	private List<Status> getUserTimelineByUid(String uid, Integer count,
			String maxId) throws WeiboException {
		return Status
				.constructStatuses(Weibo.client.get(
						WeiboConfig.getValue("baseURL")
								+ "statuses/user_timeline.json",
						new PostParameter[] { new PostParameter("uid", uid),
								new PostParameter("max_id", maxId),
								new PostParameter("count", count.toString()),
								new PostParameter("trim_user", "1") }));
	}

	private List<Status> getUserTimelineByScreenName(String screenName,
			Integer count, String maxId) throws WeiboException {
		return Status
				.constructStatuses(Weibo.client.get(
						WeiboConfig.getValue("baseURL")
								+ "statuses/user_timeline.json",
						new PostParameter[] {
								new PostParameter("screen_name", screenName),
								new PostParameter("max_id", maxId),
								new PostParameter("count", count.toString()),
								new PostParameter("trim_user", "1") }));
	}

	public byte[] getImageData(String strUrl) throws Exception {
		URL url = new URL(strUrl);
		InputStream in = url.openStream();

		int len = in.available();
		byte[] bytes = new byte[len];
		int r = in.read(bytes);
		if (len != r) {
			bytes = null;
		}
		in.close();
		return bytes;
	}

	public final void getAccessCodeFromBrowser() throws WeiboException {
		String url = _auth.authorize("code");
		BareBonesBrowserLaunch.openURL(url);
	}

	// return: number of weibo synced
	public final int sync(final String accessCode, final String database)
			throws Exception {
		AccessToken token = _auth.getAccessTokenByCode(accessCode);

		Weibo weibo = new Weibo();
		String access_token = token.getAccessToken();
		weibo.setToken(access_token);

		WeiboDB wbDB = new WeiboDB(database);

		Account ac = new Account();
		JSONObject json = ac.getUid();
		String uid = json.getString("uid");

		String maxId = "0";
		int number = 0;
		while (true) {
			List<Status> weibos = this.getUserTimelineByUid(uid, 50, maxId);
			if (weibos.size() == 0)
				break;
			for (Status item : weibos) {
				// Log
				System.out.println(String.format("%d:%s - %s", ++number,
						item.getId(), item.getText()));

				Date time = new Date(item.getCreatedAt().getTime());
				
				byte[] image = null;
				if(item.getOriginalPic() != null && !item.getOriginalPic().isEmpty())
					image = this.getImageData(item.getOriginalPic());
				
				wbDB.insertWeibo(item.getIdstr(), time, 
						item.getText(),
						image,
						item.getInReplyToStatusId());
				
				// Assume the comment number won't exceed 20
				Comments c = new Comments();
				List<Comment> cmts = c.getCommentById(item.getId());
				int cnum = 0;
				for(Comment cmt : cmts)
				{
					System.out.println(String.format("\t%d:%s - %s", ++cnum,
							item.getId(), item.getText()));
					
					Date ctime = new Date(cmt.getCreatedAt().getTime());
					wbDB.insertComment(cmt.getId(), item.getIdstr(), ctime, cmt.getText());
				}

			}

			Status last = weibos.get(weibos.size() - 1);
			Long next = Long.valueOf(last.getId()) - 1;
			maxId = next.toString();
		}

		return 0;
	}
}
