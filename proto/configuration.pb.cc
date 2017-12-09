// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: configuration.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "configuration.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Beta {

namespace {

const ::google::protobuf::Descriptor* ConfigurationProto_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ConfigurationProto_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_configuration_2eproto() {
  protobuf_AddDesc_configuration_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "configuration.proto");
  GOOGLE_CHECK(file != NULL);
  ConfigurationProto_descriptor_ = file->message_type(0);
  static const int ConfigurationProto_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigurationProto, max_depth_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigurationProto, num_trees_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigurationProto, mode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigurationProto, min_entropy_),
  };
  ConfigurationProto_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ConfigurationProto_descriptor_,
      ConfigurationProto::default_instance_,
      ConfigurationProto_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigurationProto, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ConfigurationProto, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ConfigurationProto));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_configuration_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ConfigurationProto_descriptor_, &ConfigurationProto::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_configuration_2eproto() {
  delete ConfigurationProto::default_instance_;
  delete ConfigurationProto_reflection_;
}

void protobuf_AddDesc_configuration_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\023configuration.proto\022\004Beta\"l\n\022Configura"
    "tionProto\022\024\n\tmax_depth\030\001 \002(\005:\0015\022\024\n\tnum_t"
    "rees\030\002 \002(\005:\0013\022\017\n\004mode\030\003 \002(\005:\0012\022\031\n\013min_en"
    "tropy\030\004 \002(\002:\0040.01", 137);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "configuration.proto", &protobuf_RegisterTypes);
  ConfigurationProto::default_instance_ = new ConfigurationProto();
  ConfigurationProto::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_configuration_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_configuration_2eproto {
  StaticDescriptorInitializer_configuration_2eproto() {
    protobuf_AddDesc_configuration_2eproto();
  }
} static_descriptor_initializer_configuration_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ConfigurationProto::kMaxDepthFieldNumber;
const int ConfigurationProto::kNumTreesFieldNumber;
const int ConfigurationProto::kModeFieldNumber;
const int ConfigurationProto::kMinEntropyFieldNumber;
#endif  // !_MSC_VER

ConfigurationProto::ConfigurationProto()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:Beta.ConfigurationProto)
}

void ConfigurationProto::InitAsDefaultInstance() {
}

ConfigurationProto::ConfigurationProto(const ConfigurationProto& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:Beta.ConfigurationProto)
}

void ConfigurationProto::SharedCtor() {
  _cached_size_ = 0;
  max_depth_ = 5;
  num_trees_ = 3;
  mode_ = 2;
  min_entropy_ = 0.01f;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ConfigurationProto::~ConfigurationProto() {
  // @@protoc_insertion_point(destructor:Beta.ConfigurationProto)
  SharedDtor();
}

void ConfigurationProto::SharedDtor() {
  if (this != default_instance_) {
  }
}

void ConfigurationProto::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ConfigurationProto::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ConfigurationProto_descriptor_;
}

const ConfigurationProto& ConfigurationProto::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_configuration_2eproto();
  return *default_instance_;
}

ConfigurationProto* ConfigurationProto::default_instance_ = NULL;

ConfigurationProto* ConfigurationProto::New() const {
  return new ConfigurationProto;
}

void ConfigurationProto::Clear() {
  if (_has_bits_[0 / 32] & 15) {
    max_depth_ = 5;
    num_trees_ = 3;
    mode_ = 2;
    min_entropy_ = 0.01f;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ConfigurationProto::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Beta.ConfigurationProto)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 max_depth = 1 [default = 5];
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &max_depth_)));
          set_has_max_depth();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_num_trees;
        break;
      }

      // required int32 num_trees = 2 [default = 3];
      case 2: {
        if (tag == 16) {
         parse_num_trees:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &num_trees_)));
          set_has_num_trees();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_mode;
        break;
      }

      // required int32 mode = 3 [default = 2];
      case 3: {
        if (tag == 24) {
         parse_mode:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &mode_)));
          set_has_mode();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(37)) goto parse_min_entropy;
        break;
      }

      // required float min_entropy = 4 [default = 0.01];
      case 4: {
        if (tag == 37) {
         parse_min_entropy:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &min_entropy_)));
          set_has_min_entropy();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Beta.ConfigurationProto)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Beta.ConfigurationProto)
  return false;
#undef DO_
}

void ConfigurationProto::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Beta.ConfigurationProto)
  // required int32 max_depth = 1 [default = 5];
  if (has_max_depth()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->max_depth(), output);
  }

  // required int32 num_trees = 2 [default = 3];
  if (has_num_trees()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->num_trees(), output);
  }

  // required int32 mode = 3 [default = 2];
  if (has_mode()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->mode(), output);
  }

  // required float min_entropy = 4 [default = 0.01];
  if (has_min_entropy()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(4, this->min_entropy(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Beta.ConfigurationProto)
}

::google::protobuf::uint8* ConfigurationProto::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:Beta.ConfigurationProto)
  // required int32 max_depth = 1 [default = 5];
  if (has_max_depth()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->max_depth(), target);
  }

  // required int32 num_trees = 2 [default = 3];
  if (has_num_trees()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->num_trees(), target);
  }

  // required int32 mode = 3 [default = 2];
  if (has_mode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->mode(), target);
  }

  // required float min_entropy = 4 [default = 0.01];
  if (has_min_entropy()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(4, this->min_entropy(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Beta.ConfigurationProto)
  return target;
}

int ConfigurationProto::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 max_depth = 1 [default = 5];
    if (has_max_depth()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->max_depth());
    }

    // required int32 num_trees = 2 [default = 3];
    if (has_num_trees()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->num_trees());
    }

    // required int32 mode = 3 [default = 2];
    if (has_mode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->mode());
    }

    // required float min_entropy = 4 [default = 0.01];
    if (has_min_entropy()) {
      total_size += 1 + 4;
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ConfigurationProto::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ConfigurationProto* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ConfigurationProto*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ConfigurationProto::MergeFrom(const ConfigurationProto& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_max_depth()) {
      set_max_depth(from.max_depth());
    }
    if (from.has_num_trees()) {
      set_num_trees(from.num_trees());
    }
    if (from.has_mode()) {
      set_mode(from.mode());
    }
    if (from.has_min_entropy()) {
      set_min_entropy(from.min_entropy());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ConfigurationProto::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ConfigurationProto::CopyFrom(const ConfigurationProto& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ConfigurationProto::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;

  return true;
}

void ConfigurationProto::Swap(ConfigurationProto* other) {
  if (other != this) {
    std::swap(max_depth_, other->max_depth_);
    std::swap(num_trees_, other->num_trees_);
    std::swap(mode_, other->mode_);
    std::swap(min_entropy_, other->min_entropy_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ConfigurationProto::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ConfigurationProto_descriptor_;
  metadata.reflection = ConfigurationProto_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Beta

// @@protoc_insertion_point(global_scope)