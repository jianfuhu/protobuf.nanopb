import demo_pb2, struct, sys
from google.protobuf import symbol_database
from google.protobuf.json_format import MessageToDict, ParseDict

def getObject(files):
    Objcet = {}
    obj_dict = symbol_database.Default().GetMessages(files)
    for obj_name in obj_dict:
        obj = obj_dict[obj_name]
        if obj.DESCRIPTOR.fields[0].name != "cmdId" or not obj.DESCRIPTOR.fields[0].has_default_value:
            continue
        cmdId_name = demo_pb2.cmdId_t.Name(obj.DESCRIPTOR.fields[0].default_value)
        Objcet[cmdId_name] = obj
    return Objcet
def DecodeToJsDict(msg):
    cmdId, = struct.unpack("B", msg[0])
    cmdName = demo_pb2.cmdId_t.Name(cmdId)
    obj = protoObj[cmdName]()
    obj.ParseFromString(msg[1:])
    js_dict = MessageToDict(obj)
    return js_dict
def EncodeToMessage(js_dict):
    obj = protoObj[js_dict["cmdId"]]()
    ParseDict(js_dict, obj)
    return struct.pack("B", demo_pb2.cmdId_t.Value(js_dict["cmdId"])) + obj.SerializeToString()

protoObj = getObject(["demo.proto"])
msg = EncodeToMessage({"cmdId":"SayHello", "msg":"hello world."})
print "Encode[msgSayHello]:",
for c in msg:
    c, = struct.unpack("B", c)
    print "%02x" % c, 
else:
    print ""

print DecodeToJsDict(msg)