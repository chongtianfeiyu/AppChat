﻿package  {
	import flash.display.Sprite;
	import net.NetEngine;
	import flash.text.TextField;
	import fl.controls.TextArea;
	import fl.controls.TextInput;
	import fl.controls.Button;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.events.MouseEvent;
	import protocol.loginServer;
	import flash.system.IME;
	
	public class ChatClient extends Sprite
	{
		
		//flide
		
		//ip
		public var txtIp:TextField;
		
		//port
		public var txtPort:TextField;
		
		//userName
		public var txtUserName:TextField;
		
		//content
		public var txtContent:TextArea;
		
		//message
		public var txtSendMsg:TextInput;
		
		//连接按钮
		public var btnConn:Button;
		
		//登录按钮
		public var btnLogin:Button;
		
		//发送按钮
		public var btnSendMsg:Button;
		
		
		private var socketEngine:NetEngine;
		
		public function ChatClient() 
		{
			//socketEngine.connect(txtIp.text,int(txtPort.text);
			// constructor code
			
			IME.enabled = true;
			
			initNet();
			listener();
			
		}
		
		private function initNet():void
		{
			socketEngine = new NetEngine();
			socketEngine.addEventListener(Event.CONNECT,connectionHandler,false,0,true);
			socketEngine.addEventListener(IOErrorEvent.IO_ERROR,connIoErrorHandler,false,0,true);
		}
		
		private function listener():void
		{
			btnConn.addEventListener(MouseEvent.CLICK,connClickHandler,false,0,true);
			btnSendMsg.addEventListener(MouseEvent.CLICK,sendClickHandler,false,0,true);
			btnLogin.addEventListener(MouseEvent.CLICK,loginClickHandler,false,0,true);
		}
		
		private function connectionHandler(event:Event):void
		{
			txtContent.text += "connectionSucceed\n";
		}
		
		private function connIoErrorHandler(event:IOErrorEvent):void
		{
			txtContent.text += "connectionFault\n";
		}
		
		private function connClickHandler(event:MouseEvent):void
		{
			socketEngine.connect(txtIp.text,int(txtPort.text));
		}
		
		//登录聊天
		private function loginClickHandler(event:MouseEvent):void
		{
			var login:loginServer = new loginServer();
			login.userID = txtUserName.text;
			socketEngine.sendMessage(login);
			
		}
		
		private function sendClickHandler(event:MouseEvent):void
		{
			
		}
		
		
		
		
	}
	
}
