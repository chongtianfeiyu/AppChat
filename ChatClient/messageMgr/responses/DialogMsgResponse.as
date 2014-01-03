package messageMgr.responses
{
	import com.netease.protobuf.Message;
	
	import messageMgr.NetResponseBase;
	
	/**
	 * 聊天内容协议 
	 * @author taojiang
	 * 
	 */	
	public class DialogMsgResponse extends NetResponseBase
	{
		public function DialogMsgResponse()
		{
			super();
		}
		
		public override function onResult(msg:Message):void
		{
			trace(msg.toString());
		}
		
	}
}