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
	public dynamic final class errorMsg extends com.netease.protobuf.Message {
		/**
		 *  @private
		 */
		public static const XYID:FieldDescriptor$TYPE_ENUM = new FieldDescriptor$TYPE_ENUM("protocol.errorMsg.XYID", "xYID", (1 << 3) | com.netease.protobuf.WireType.VARINT, protocol.XY_ID);

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
				return protocol.XY_ID.XIYD_THREE_EEROR;
			}
			return XYID$field;
		}

		/**
		 *  @private
		 */
		public static const ERROR_CODE:FieldDescriptor$TYPE_INT32 = new FieldDescriptor$TYPE_INT32("protocol.errorMsg.error_code", "errorCode", (2 << 3) | com.netease.protobuf.WireType.VARINT);

		private var error_code$field:int;

		public function clearErrorCode():void {
			hasField$0 &= 0xfffffffd;
			error_code$field = new int();
		}

		public function get hasErrorCode():Boolean {
			return (hasField$0 & 0x2) != 0;
		}

		public function set errorCode(value:int):void {
			hasField$0 |= 0x2;
			error_code$field = value;
		}

		public function get errorCode():int {
			return error_code$field;
		}

		/**
		 *  @private
		 */
		public static const ERROR_TYPE:FieldDescriptor$TYPE_INT32 = new FieldDescriptor$TYPE_INT32("protocol.errorMsg.error_type", "errorType", (3 << 3) | com.netease.protobuf.WireType.VARINT);

		private var error_type$field:int;

		public function clearErrorType():void {
			hasField$0 &= 0xfffffffb;
			error_type$field = new int();
		}

		public function get hasErrorType():Boolean {
			return (hasField$0 & 0x4) != 0;
		}

		public function set errorType(value:int):void {
			hasField$0 |= 0x4;
			error_type$field = value;
		}

		public function get errorType():int {
			return error_type$field;
		}

		/**
		 *  @private
		 */
		public static const ERROR_MSG:FieldDescriptor$TYPE_STRING = new FieldDescriptor$TYPE_STRING("protocol.errorMsg.error_msg", "errorMsg", (4 << 3) | com.netease.protobuf.WireType.LENGTH_DELIMITED);

		private var error_msg$field:String;

		public function clearErrorMsg():void {
			error_msg$field = null;
		}

		public function get hasErrorMsg():Boolean {
			return error_msg$field != null;
		}

		public function set errorMsg(value:String):void {
			error_msg$field = value;
		}

		public function get errorMsg():String {
			return error_msg$field;
		}

		/**
		 *  @private
		 */
		override used_by_generated_code final function writeToBuffer(output:com.netease.protobuf.WritingBuffer):void {
			if (hasXYID) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 1);
				com.netease.protobuf.WriteUtils.write$TYPE_ENUM(output, XYID$field);
			}
			if (hasErrorCode) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 2);
				com.netease.protobuf.WriteUtils.write$TYPE_INT32(output, error_code$field);
			}
			if (hasErrorType) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.VARINT, 3);
				com.netease.protobuf.WriteUtils.write$TYPE_INT32(output, error_type$field);
			}
			if (hasErrorMsg) {
				com.netease.protobuf.WriteUtils.writeTag(output, com.netease.protobuf.WireType.LENGTH_DELIMITED, 4);
				com.netease.protobuf.WriteUtils.write$TYPE_STRING(output, error_msg$field);
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
			var error_code$count:uint = 0;
			var error_type$count:uint = 0;
			var error_msg$count:uint = 0;
			while (input.bytesAvailable > bytesAfterSlice) {
				var tag:uint = com.netease.protobuf.ReadUtils.read$TYPE_UINT32(input);
				switch (tag >> 3) {
				case 1:
					if (XYID$count != 0) {
						throw new flash.errors.IOError('Bad data format: errorMsg.xYID cannot be set twice.');
					}
					++XYID$count;
					this.xYID = com.netease.protobuf.ReadUtils.read$TYPE_ENUM(input);
					break;
				case 2:
					if (error_code$count != 0) {
						throw new flash.errors.IOError('Bad data format: errorMsg.errorCode cannot be set twice.');
					}
					++error_code$count;
					this.errorCode = com.netease.protobuf.ReadUtils.read$TYPE_INT32(input);
					break;
				case 3:
					if (error_type$count != 0) {
						throw new flash.errors.IOError('Bad data format: errorMsg.errorType cannot be set twice.');
					}
					++error_type$count;
					this.errorType = com.netease.protobuf.ReadUtils.read$TYPE_INT32(input);
					break;
				case 4:
					if (error_msg$count != 0) {
						throw new flash.errors.IOError('Bad data format: errorMsg.errorMsg cannot be set twice.');
					}
					++error_msg$count;
					this.errorMsg = com.netease.protobuf.ReadUtils.read$TYPE_STRING(input);
					break;
				default:
					super.readUnknown(input, tag);
					break;
				}
			}
		}

	}
}
