package protocol {
	import com.netease.protobuf.*;
	use namespace com.netease.protobuf.used_by_generated_code;
	import com.netease.protobuf.fieldDescriptors.*;
	import flash.utils.Endian;
	import flash.utils.IDataInput;
	import flash.utils.IDataOutput;
	import flash.utils.IExternalizable;
	import flash.errors.IOError;
	import protocol.XY_ID;
	// @@protoc_insertion_point(imports)

	// @@protoc_insertion_point(class_metadata)
	public dynamic final class loginServer extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const XYID:FieldDescriptor$TYPE_ENUM = new FieldDescriptor$TYPE_ENUM("protocol.loginServer.XYID", "xYID", (1 << 3) | com.netease.protobuf.WireType.VARINT, protocol.XY_ID);

		private var XYID$field:int;

		private var hasField$0:uint = 0;

		public function clearXYID():void {
			hasField$0 &= 0xfffffffe;
			XYID$field = new int();
		}

		public function get hasXYID():Boolean {
			return (hasField$0 & 0x1) != 0;
		}

		public function set xYID(value:int):void {
			hasField$0 |= 0x1;
			XYID$field = value;
		}

		public function get xYID():int {
			if(!hasXYID) {
				return protocol.XY_ID.XYID_LOGIN;
			}
			return XYID$field;
		}

		/**
		 *  @private
		 */
		public static const USERID:FieldDescriptor$TYPE_STRING = new FieldDescriptor$TYPE_STRING("protocol.loginServer.userID", "userID", (2 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var userID$field:String;

		public function clearUserID():void {
			userID$field = null;
		}

		public function get hasUserID():Boolean {
			return userID$field != null;
		}

		public function set userID(value:String):void {
			userID$field = value;
		}

		public function get userID():String {
			return userID$field;
		}

		/**
		 *  @private
		 */
		override used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasXYID) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write$TYPE_ENUM(output, XYID$field);
			}
			if (hasUserID) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 2);
				com.netease.protobuf.WriteUtils.write$TYPE_STRING(output, userID$field);
			}
			for (var fieldKey:* in this) {
				super.writeUnknown(output, fieldKey);
			}
		}

		/**
		 *  @private
		 */
		override used_by_generated_code final function readFromSlice(input:flash.utils.IDataInput, bytesAfterSlice:uint):void {
			var XYID$count:uint = 0;
			var userID$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read$TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (XYID$count != 0) {
						throw new flash.errors.IOError('Bad data format: loginServer.xYID cannot be set twice.');
					}
					++XYID$count;
					this.xYID = com.netease.protobuf.ReadUtils.read$TYPE_ENUM(input);
					break;
				case 2:
					if (userID$count != 0) {
						throw new flash.errors.IOError('Bad data format: loginServer.userID cannot be set twice.');
					}
					++userID$count;
					this.userID = com.netease.protobuf.ReadUtils.read$TYPE_STRING(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
