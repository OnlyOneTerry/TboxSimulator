// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: envelope.proto

#include "envelope.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace EvelopeNS {
constexpr Envelope::Envelope(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : version_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , vid_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , msg_(nullptr)
  , time_(int64_t{0})
  , receivetime_(int64_t{0})
  , resend_(false)
  , source_(0)
{}
struct EnvelopeDefaultTypeInternal {
  constexpr EnvelopeDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~EnvelopeDefaultTypeInternal() {}
  union {
    Envelope _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT EnvelopeDefaultTypeInternal _Envelope_default_instance_;
}  // namespace EvelopeNS
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_envelope_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_envelope_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_envelope_2eproto = nullptr;

const uint32_t TableStruct_envelope_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, version_),
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, time_),
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, vid_),
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, msg_),
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, resend_),
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, receivetime_),
  PROTOBUF_FIELD_OFFSET(::EvelopeNS::Envelope, source_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::EvelopeNS::Envelope)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::EvelopeNS::_Envelope_default_instance_),
};

const char descriptor_table_protodef_envelope_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\016envelope.proto\022\tEvelopeNS\032\rmessage.pro"
  "to\"\237\001\n\010Envelope\022\017\n\007version\030\001 \001(\t\022\014\n\004time"
  "\030\002 \001(\003\022\013\n\003vid\030\003 \001(\t\022\037\n\003msg\030\004 \001(\0132\022.Messa"
  "geNS.Message\022\016\n\006reSend\030\005 \001(\010\022\023\n\013receiveT"
  "ime\030\006 \001(\003\022!\n\006source\030\007 \001(\0162\021.EvelopeNS.So"
  "urce*\'\n\006Source\022\010\n\004TBOX\020\000\022\n\n\006MOBILE\020\001\022\007\n\003"
  "OBD\020\002B\036\n\rcom.iov.protoB\rEnvelopeProtoP\000b"
  "\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_envelope_2eproto_deps[1] = {
  &::descriptor_table_message_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_envelope_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_envelope_2eproto = {
  false, false, 287, descriptor_table_protodef_envelope_2eproto, "envelope.proto", 
  &descriptor_table_envelope_2eproto_once, descriptor_table_envelope_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_envelope_2eproto::offsets,
  file_level_metadata_envelope_2eproto, file_level_enum_descriptors_envelope_2eproto, file_level_service_descriptors_envelope_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_envelope_2eproto_getter() {
  return &descriptor_table_envelope_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_envelope_2eproto(&descriptor_table_envelope_2eproto);
namespace EvelopeNS {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Source_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_envelope_2eproto);
  return file_level_enum_descriptors_envelope_2eproto[0];
}
bool Source_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class Envelope::_Internal {
 public:
  static const ::MessageNS::Message& msg(const Envelope* msg);
};

const ::MessageNS::Message&
Envelope::_Internal::msg(const Envelope* msg) {
  return *msg->msg_;
}
void Envelope::clear_msg() {
  if (GetArenaForAllocation() == nullptr && msg_ != nullptr) {
    delete msg_;
  }
  msg_ = nullptr;
}
Envelope::Envelope(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:EvelopeNS.Envelope)
}
Envelope::Envelope(const Envelope& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  version_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    version_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_version().empty()) {
    version_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_version(), 
      GetArenaForAllocation());
  }
  vid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    vid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_vid().empty()) {
    vid_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_vid(), 
      GetArenaForAllocation());
  }
  if (from._internal_has_msg()) {
    msg_ = new ::MessageNS::Message(*from.msg_);
  } else {
    msg_ = nullptr;
  }
  ::memcpy(&time_, &from.time_,
    static_cast<size_t>(reinterpret_cast<char*>(&source_) -
    reinterpret_cast<char*>(&time_)) + sizeof(source_));
  // @@protoc_insertion_point(copy_constructor:EvelopeNS.Envelope)
}

inline void Envelope::SharedCtor() {
version_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  version_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
vid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  vid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&msg_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&source_) -
    reinterpret_cast<char*>(&msg_)) + sizeof(source_));
}

Envelope::~Envelope() {
  // @@protoc_insertion_point(destructor:EvelopeNS.Envelope)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Envelope::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  version_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  vid_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete msg_;
}

void Envelope::ArenaDtor(void* object) {
  Envelope* _this = reinterpret_cast< Envelope* >(object);
  (void)_this;
}
void Envelope::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Envelope::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Envelope::Clear() {
// @@protoc_insertion_point(message_clear_start:EvelopeNS.Envelope)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  version_.ClearToEmpty();
  vid_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && msg_ != nullptr) {
    delete msg_;
  }
  msg_ = nullptr;
  ::memset(&time_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&source_) -
      reinterpret_cast<char*>(&time_)) + sizeof(source_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Envelope::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string version = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_version();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "EvelopeNS.Envelope.version"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int64 time = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          time_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string vid = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_vid();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "EvelopeNS.Envelope.vid"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .MessageNS.Message msg = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          ptr = ctx->ParseMessage(_internal_mutable_msg(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bool reSend = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          resend_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int64 receiveTime = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          receivetime_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .EvelopeNS.Source source = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 56)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_source(static_cast<::EvelopeNS::Source>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Envelope::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:EvelopeNS.Envelope)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string version = 1;
  if (!this->_internal_version().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_version().data(), static_cast<int>(this->_internal_version().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "EvelopeNS.Envelope.version");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_version(), target);
  }

  // int64 time = 2;
  if (this->_internal_time() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(2, this->_internal_time(), target);
  }

  // string vid = 3;
  if (!this->_internal_vid().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_vid().data(), static_cast<int>(this->_internal_vid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "EvelopeNS.Envelope.vid");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_vid(), target);
  }

  // .MessageNS.Message msg = 4;
  if (this->_internal_has_msg()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        4, _Internal::msg(this), target, stream);
  }

  // bool reSend = 5;
  if (this->_internal_resend() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(5, this->_internal_resend(), target);
  }

  // int64 receiveTime = 6;
  if (this->_internal_receivetime() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(6, this->_internal_receivetime(), target);
  }

  // .EvelopeNS.Source source = 7;
  if (this->_internal_source() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      7, this->_internal_source(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:EvelopeNS.Envelope)
  return target;
}

size_t Envelope::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:EvelopeNS.Envelope)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string version = 1;
  if (!this->_internal_version().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_version());
  }

  // string vid = 3;
  if (!this->_internal_vid().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_vid());
  }

  // .MessageNS.Message msg = 4;
  if (this->_internal_has_msg()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *msg_);
  }

  // int64 time = 2;
  if (this->_internal_time() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64SizePlusOne(this->_internal_time());
  }

  // int64 receiveTime = 6;
  if (this->_internal_receivetime() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64SizePlusOne(this->_internal_receivetime());
  }

  // bool reSend = 5;
  if (this->_internal_resend() != 0) {
    total_size += 1 + 1;
  }

  // .EvelopeNS.Source source = 7;
  if (this->_internal_source() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_source());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Envelope::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Envelope::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Envelope::GetClassData() const { return &_class_data_; }

void Envelope::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Envelope *>(to)->MergeFrom(
      static_cast<const Envelope &>(from));
}


void Envelope::MergeFrom(const Envelope& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:EvelopeNS.Envelope)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_version().empty()) {
    _internal_set_version(from._internal_version());
  }
  if (!from._internal_vid().empty()) {
    _internal_set_vid(from._internal_vid());
  }
  if (from._internal_has_msg()) {
    _internal_mutable_msg()->::MessageNS::Message::MergeFrom(from._internal_msg());
  }
  if (from._internal_time() != 0) {
    _internal_set_time(from._internal_time());
  }
  if (from._internal_receivetime() != 0) {
    _internal_set_receivetime(from._internal_receivetime());
  }
  if (from._internal_resend() != 0) {
    _internal_set_resend(from._internal_resend());
  }
  if (from._internal_source() != 0) {
    _internal_set_source(from._internal_source());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Envelope::CopyFrom(const Envelope& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:EvelopeNS.Envelope)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Envelope::IsInitialized() const {
  return true;
}

void Envelope::InternalSwap(Envelope* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &version_, lhs_arena,
      &other->version_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &vid_, lhs_arena,
      &other->vid_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Envelope, source_)
      + sizeof(Envelope::source_)
      - PROTOBUF_FIELD_OFFSET(Envelope, msg_)>(
          reinterpret_cast<char*>(&msg_),
          reinterpret_cast<char*>(&other->msg_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Envelope::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_envelope_2eproto_getter, &descriptor_table_envelope_2eproto_once,
      file_level_metadata_envelope_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace EvelopeNS
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::EvelopeNS::Envelope* Arena::CreateMaybeMessage< ::EvelopeNS::Envelope >(Arena* arena) {
  return Arena::CreateMessageInternal< ::EvelopeNS::Envelope >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
