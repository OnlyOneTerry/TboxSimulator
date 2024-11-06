// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: lock.proto

#include "lock.pb.h"

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
namespace LockNS {
constexpr Lock::Lock(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : taskid_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , lockrequest_(nullptr)
  , lockresponse_(nullptr){}
struct LockDefaultTypeInternal {
  constexpr LockDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~LockDefaultTypeInternal() {}
  union {
    Lock _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT LockDefaultTypeInternal _Lock_default_instance_;
constexpr LockRequest::LockRequest(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : lockopt_(0)
{}
struct LockRequestDefaultTypeInternal {
  constexpr LockRequestDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~LockRequestDefaultTypeInternal() {}
  union {
    LockRequest _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT LockRequestDefaultTypeInternal _LockRequest_default_instance_;
constexpr LockResponse::LockResponse(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : resultcode_(0)

  , lockstatus_(0)
{}
struct LockResponseDefaultTypeInternal {
  constexpr LockResponseDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~LockResponseDefaultTypeInternal() {}
  union {
    LockResponse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT LockResponseDefaultTypeInternal _LockResponse_default_instance_;
}  // namespace LockNS
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_lock_2eproto[3];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_lock_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_lock_2eproto = nullptr;

const uint32_t TableStruct_lock_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::LockNS::Lock, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::LockNS::Lock, taskid_),
  PROTOBUF_FIELD_OFFSET(::LockNS::Lock, lockrequest_),
  PROTOBUF_FIELD_OFFSET(::LockNS::Lock, lockresponse_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::LockNS::LockRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::LockNS::LockRequest, lockopt_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::LockNS::LockResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::LockNS::LockResponse, resultcode_),
  PROTOBUF_FIELD_OFFSET(::LockNS::LockResponse, lockstatus_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::LockNS::Lock)},
  { 9, -1, -1, sizeof(::LockNS::LockRequest)},
  { 16, -1, -1, sizeof(::LockNS::LockResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::LockNS::_Lock_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::LockNS::_LockRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::LockNS::_LockResponse_default_instance_),
};

const char descriptor_table_protodef_lock_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nlock.proto\022\006LockNS\"l\n\004Lock\022\016\n\006taskID\030\001"
  " \001(\t\022(\n\013lockRequest\030\002 \001(\0132\023.LockNS.LockR"
  "equest\022*\n\014lockResponse\030\003 \001(\0132\024.LockNS.Lo"
  "ckResponse\"/\n\013LockRequest\022 \n\007lockOpt\030\001 \001"
  "(\0162\017.LockNS.LockOpt\"b\n\014LockResponse\022*\n\nr"
  "esultCode\030\001 \001(\0162\026.LockNS.LockResultCode\022"
  "&\n\nlockStatus\030\002 \001(\0162\022.LockNS.LockStatus*"
  "C\n\007LockOpt\022\013\n\007INVALID\020\000\022\014\n\010LOCK_REQ\020\001\022\016\n"
  "\nUNLOCK_REQ\020\002\022\r\n\tQUERY_REQ\020\003*\"\n\nLockStat"
  "us\022\n\n\006UNLOCK\020\000\022\010\n\004LOCK\020\001*)\n\016LockResultCo"
  "de\022\013\n\007SUCCESS\020\000\022\n\n\006FAILED\020\001B\032\n\rcom.iov.p"
  "rotoB\tLockProtob\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_lock_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_lock_2eproto = {
  false, false, 463, descriptor_table_protodef_lock_2eproto, "lock.proto", 
  &descriptor_table_lock_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_lock_2eproto::offsets,
  file_level_metadata_lock_2eproto, file_level_enum_descriptors_lock_2eproto, file_level_service_descriptors_lock_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_lock_2eproto_getter() {
  return &descriptor_table_lock_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_lock_2eproto(&descriptor_table_lock_2eproto);
namespace LockNS {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* LockOpt_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_lock_2eproto);
  return file_level_enum_descriptors_lock_2eproto[0];
}
bool LockOpt_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* LockStatus_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_lock_2eproto);
  return file_level_enum_descriptors_lock_2eproto[1];
}
bool LockStatus_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* LockResultCode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_lock_2eproto);
  return file_level_enum_descriptors_lock_2eproto[2];
}
bool LockResultCode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class Lock::_Internal {
 public:
  static const ::LockNS::LockRequest& lockrequest(const Lock* msg);
  static const ::LockNS::LockResponse& lockresponse(const Lock* msg);
};

const ::LockNS::LockRequest&
Lock::_Internal::lockrequest(const Lock* msg) {
  return *msg->lockrequest_;
}
const ::LockNS::LockResponse&
Lock::_Internal::lockresponse(const Lock* msg) {
  return *msg->lockresponse_;
}
Lock::Lock(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:LockNS.Lock)
}
Lock::Lock(const Lock& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  taskid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    taskid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_taskid().empty()) {
    taskid_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_taskid(), 
      GetArenaForAllocation());
  }
  if (from._internal_has_lockrequest()) {
    lockrequest_ = new ::LockNS::LockRequest(*from.lockrequest_);
  } else {
    lockrequest_ = nullptr;
  }
  if (from._internal_has_lockresponse()) {
    lockresponse_ = new ::LockNS::LockResponse(*from.lockresponse_);
  } else {
    lockresponse_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:LockNS.Lock)
}

inline void Lock::SharedCtor() {
taskid_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  taskid_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&lockrequest_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&lockresponse_) -
    reinterpret_cast<char*>(&lockrequest_)) + sizeof(lockresponse_));
}

Lock::~Lock() {
  // @@protoc_insertion_point(destructor:LockNS.Lock)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Lock::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  taskid_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete lockrequest_;
  if (this != internal_default_instance()) delete lockresponse_;
}

void Lock::ArenaDtor(void* object) {
  Lock* _this = reinterpret_cast< Lock* >(object);
  (void)_this;
}
void Lock::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Lock::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Lock::Clear() {
// @@protoc_insertion_point(message_clear_start:LockNS.Lock)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  taskid_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && lockrequest_ != nullptr) {
    delete lockrequest_;
  }
  lockrequest_ = nullptr;
  if (GetArenaForAllocation() == nullptr && lockresponse_ != nullptr) {
    delete lockresponse_;
  }
  lockresponse_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Lock::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string taskID = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_taskid();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "LockNS.Lock.taskID"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .LockNS.LockRequest lockRequest = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_lockrequest(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .LockNS.LockResponse lockResponse = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_lockresponse(), ptr);
          CHK_(ptr);
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

uint8_t* Lock::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:LockNS.Lock)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string taskID = 1;
  if (!this->_internal_taskid().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_taskid().data(), static_cast<int>(this->_internal_taskid().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "LockNS.Lock.taskID");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_taskid(), target);
  }

  // .LockNS.LockRequest lockRequest = 2;
  if (this->_internal_has_lockrequest()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::lockrequest(this), target, stream);
  }

  // .LockNS.LockResponse lockResponse = 3;
  if (this->_internal_has_lockresponse()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        3, _Internal::lockresponse(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:LockNS.Lock)
  return target;
}

size_t Lock::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:LockNS.Lock)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string taskID = 1;
  if (!this->_internal_taskid().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_taskid());
  }

  // .LockNS.LockRequest lockRequest = 2;
  if (this->_internal_has_lockrequest()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *lockrequest_);
  }

  // .LockNS.LockResponse lockResponse = 3;
  if (this->_internal_has_lockresponse()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *lockresponse_);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Lock::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Lock::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Lock::GetClassData() const { return &_class_data_; }

void Lock::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Lock *>(to)->MergeFrom(
      static_cast<const Lock &>(from));
}


void Lock::MergeFrom(const Lock& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:LockNS.Lock)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_taskid().empty()) {
    _internal_set_taskid(from._internal_taskid());
  }
  if (from._internal_has_lockrequest()) {
    _internal_mutable_lockrequest()->::LockNS::LockRequest::MergeFrom(from._internal_lockrequest());
  }
  if (from._internal_has_lockresponse()) {
    _internal_mutable_lockresponse()->::LockNS::LockResponse::MergeFrom(from._internal_lockresponse());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Lock::CopyFrom(const Lock& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:LockNS.Lock)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Lock::IsInitialized() const {
  return true;
}

void Lock::InternalSwap(Lock* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &taskid_, lhs_arena,
      &other->taskid_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Lock, lockresponse_)
      + sizeof(Lock::lockresponse_)
      - PROTOBUF_FIELD_OFFSET(Lock, lockrequest_)>(
          reinterpret_cast<char*>(&lockrequest_),
          reinterpret_cast<char*>(&other->lockrequest_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Lock::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_lock_2eproto_getter, &descriptor_table_lock_2eproto_once,
      file_level_metadata_lock_2eproto[0]);
}

// ===================================================================

class LockRequest::_Internal {
 public:
};

LockRequest::LockRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:LockNS.LockRequest)
}
LockRequest::LockRequest(const LockRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  lockopt_ = from.lockopt_;
  // @@protoc_insertion_point(copy_constructor:LockNS.LockRequest)
}

inline void LockRequest::SharedCtor() {
lockopt_ = 0;
}

LockRequest::~LockRequest() {
  // @@protoc_insertion_point(destructor:LockNS.LockRequest)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void LockRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void LockRequest::ArenaDtor(void* object) {
  LockRequest* _this = reinterpret_cast< LockRequest* >(object);
  (void)_this;
}
void LockRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void LockRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void LockRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:LockNS.LockRequest)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  lockopt_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* LockRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .LockNS.LockOpt lockOpt = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_lockopt(static_cast<::LockNS::LockOpt>(val));
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

uint8_t* LockRequest::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:LockNS.LockRequest)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .LockNS.LockOpt lockOpt = 1;
  if (this->_internal_lockopt() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_lockopt(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:LockNS.LockRequest)
  return target;
}

size_t LockRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:LockNS.LockRequest)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .LockNS.LockOpt lockOpt = 1;
  if (this->_internal_lockopt() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_lockopt());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData LockRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    LockRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*LockRequest::GetClassData() const { return &_class_data_; }

void LockRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<LockRequest *>(to)->MergeFrom(
      static_cast<const LockRequest &>(from));
}


void LockRequest::MergeFrom(const LockRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:LockNS.LockRequest)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_lockopt() != 0) {
    _internal_set_lockopt(from._internal_lockopt());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void LockRequest::CopyFrom(const LockRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:LockNS.LockRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LockRequest::IsInitialized() const {
  return true;
}

void LockRequest::InternalSwap(LockRequest* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(lockopt_, other->lockopt_);
}

::PROTOBUF_NAMESPACE_ID::Metadata LockRequest::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_lock_2eproto_getter, &descriptor_table_lock_2eproto_once,
      file_level_metadata_lock_2eproto[1]);
}

// ===================================================================

class LockResponse::_Internal {
 public:
};

LockResponse::LockResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:LockNS.LockResponse)
}
LockResponse::LockResponse(const LockResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&resultcode_, &from.resultcode_,
    static_cast<size_t>(reinterpret_cast<char*>(&lockstatus_) -
    reinterpret_cast<char*>(&resultcode_)) + sizeof(lockstatus_));
  // @@protoc_insertion_point(copy_constructor:LockNS.LockResponse)
}

inline void LockResponse::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&resultcode_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&lockstatus_) -
    reinterpret_cast<char*>(&resultcode_)) + sizeof(lockstatus_));
}

LockResponse::~LockResponse() {
  // @@protoc_insertion_point(destructor:LockNS.LockResponse)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void LockResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void LockResponse::ArenaDtor(void* object) {
  LockResponse* _this = reinterpret_cast< LockResponse* >(object);
  (void)_this;
}
void LockResponse::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void LockResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void LockResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:LockNS.LockResponse)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&resultcode_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&lockstatus_) -
      reinterpret_cast<char*>(&resultcode_)) + sizeof(lockstatus_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* LockResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // .LockNS.LockResultCode resultCode = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_resultcode(static_cast<::LockNS::LockResultCode>(val));
        } else
          goto handle_unusual;
        continue;
      // .LockNS.LockStatus lockStatus = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_lockstatus(static_cast<::LockNS::LockStatus>(val));
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

uint8_t* LockResponse::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:LockNS.LockResponse)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // .LockNS.LockResultCode resultCode = 1;
  if (this->_internal_resultcode() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_resultcode(), target);
  }

  // .LockNS.LockStatus lockStatus = 2;
  if (this->_internal_lockstatus() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      2, this->_internal_lockstatus(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:LockNS.LockResponse)
  return target;
}

size_t LockResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:LockNS.LockResponse)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .LockNS.LockResultCode resultCode = 1;
  if (this->_internal_resultcode() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_resultcode());
  }

  // .LockNS.LockStatus lockStatus = 2;
  if (this->_internal_lockstatus() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_lockstatus());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData LockResponse::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    LockResponse::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*LockResponse::GetClassData() const { return &_class_data_; }

void LockResponse::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<LockResponse *>(to)->MergeFrom(
      static_cast<const LockResponse &>(from));
}


void LockResponse::MergeFrom(const LockResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:LockNS.LockResponse)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_resultcode() != 0) {
    _internal_set_resultcode(from._internal_resultcode());
  }
  if (from._internal_lockstatus() != 0) {
    _internal_set_lockstatus(from._internal_lockstatus());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void LockResponse::CopyFrom(const LockResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:LockNS.LockResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LockResponse::IsInitialized() const {
  return true;
}

void LockResponse::InternalSwap(LockResponse* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(LockResponse, lockstatus_)
      + sizeof(LockResponse::lockstatus_)
      - PROTOBUF_FIELD_OFFSET(LockResponse, resultcode_)>(
          reinterpret_cast<char*>(&resultcode_),
          reinterpret_cast<char*>(&other->resultcode_));
}

::PROTOBUF_NAMESPACE_ID::Metadata LockResponse::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_lock_2eproto_getter, &descriptor_table_lock_2eproto_once,
      file_level_metadata_lock_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace LockNS
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::LockNS::Lock* Arena::CreateMaybeMessage< ::LockNS::Lock >(Arena* arena) {
  return Arena::CreateMessageInternal< ::LockNS::Lock >(arena);
}
template<> PROTOBUF_NOINLINE ::LockNS::LockRequest* Arena::CreateMaybeMessage< ::LockNS::LockRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::LockNS::LockRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::LockNS::LockResponse* Arena::CreateMaybeMessage< ::LockNS::LockResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::LockNS::LockResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
