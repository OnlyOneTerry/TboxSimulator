// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gb32960.proto

#include "gb32960.pb.h"

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
namespace Gb32960NS {
constexpr Gb32960::Gb32960(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct Gb32960DefaultTypeInternal {
  constexpr Gb32960DefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~Gb32960DefaultTypeInternal() {}
  union {
    Gb32960 _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT Gb32960DefaultTypeInternal _Gb32960_default_instance_;
}  // namespace Gb32960NS
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_gb32960_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_gb32960_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_gb32960_2eproto = nullptr;

const uint32_t TableStruct_gb32960_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Gb32960NS::Gb32960, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Gb32960NS::Gb32960, data_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Gb32960NS::Gb32960)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Gb32960NS::_Gb32960_default_instance_),
};

const char descriptor_table_protodef_gb32960_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rgb32960.proto\022\tGb32960NS\"\027\n\007Gb32960\022\014\n"
  "\004data\030\001 \001(\014B\035\n\rcom.iov.protoB\014Gb32960Pro"
  "tob\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_gb32960_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_gb32960_2eproto = {
  false, false, 90, descriptor_table_protodef_gb32960_2eproto, "gb32960.proto", 
  &descriptor_table_gb32960_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_gb32960_2eproto::offsets,
  file_level_metadata_gb32960_2eproto, file_level_enum_descriptors_gb32960_2eproto, file_level_service_descriptors_gb32960_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_gb32960_2eproto_getter() {
  return &descriptor_table_gb32960_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_gb32960_2eproto(&descriptor_table_gb32960_2eproto);
namespace Gb32960NS {

// ===================================================================

class Gb32960::_Internal {
 public:
};

Gb32960::Gb32960(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:Gb32960NS.Gb32960)
}
Gb32960::Gb32960(const Gb32960& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data().empty()) {
    data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_data(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:Gb32960NS.Gb32960)
}

inline void Gb32960::SharedCtor() {
data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Gb32960::~Gb32960() {
  // @@protoc_insertion_point(destructor:Gb32960NS.Gb32960)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Gb32960::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  data_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Gb32960::ArenaDtor(void* object) {
  Gb32960* _this = reinterpret_cast< Gb32960* >(object);
  (void)_this;
}
void Gb32960::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Gb32960::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Gb32960::Clear() {
// @@protoc_insertion_point(message_clear_start:Gb32960NS.Gb32960)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Gb32960::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bytes data = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_data();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
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

uint8_t* Gb32960::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Gb32960NS.Gb32960)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes data = 1;
  if (!this->_internal_data().empty()) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_data(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Gb32960NS.Gb32960)
  return target;
}

size_t Gb32960::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Gb32960NS.Gb32960)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes data = 1;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_data());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Gb32960::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Gb32960::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Gb32960::GetClassData() const { return &_class_data_; }

void Gb32960::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Gb32960 *>(to)->MergeFrom(
      static_cast<const Gb32960 &>(from));
}


void Gb32960::MergeFrom(const Gb32960& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Gb32960NS.Gb32960)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_data().empty()) {
    _internal_set_data(from._internal_data());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Gb32960::CopyFrom(const Gb32960& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Gb32960NS.Gb32960)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Gb32960::IsInitialized() const {
  return true;
}

void Gb32960::InternalSwap(Gb32960* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &data_, lhs_arena,
      &other->data_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata Gb32960::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_gb32960_2eproto_getter, &descriptor_table_gb32960_2eproto_once,
      file_level_metadata_gb32960_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Gb32960NS
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Gb32960NS::Gb32960* Arena::CreateMaybeMessage< ::Gb32960NS::Gb32960 >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Gb32960NS::Gb32960 >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
