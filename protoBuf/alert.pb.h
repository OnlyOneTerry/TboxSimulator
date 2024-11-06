// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: alert.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_alert_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_alert_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_alert_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_alert_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_alert_2eproto;
namespace AlertNS {
class Alert;
struct AlertDefaultTypeInternal;
extern AlertDefaultTypeInternal _Alert_default_instance_;
class AlertMsg;
struct AlertMsgDefaultTypeInternal;
extern AlertMsgDefaultTypeInternal _AlertMsg_default_instance_;
}  // namespace AlertNS
PROTOBUF_NAMESPACE_OPEN
template<> ::AlertNS::Alert* Arena::CreateMaybeMessage<::AlertNS::Alert>(Arena*);
template<> ::AlertNS::AlertMsg* Arena::CreateMaybeMessage<::AlertNS::AlertMsg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace AlertNS {

enum AlertItem : int {
  UNKNOWN = 0,
  ALERT_Vibration = 1,
  ALERT_Position_Move = 2,
  ALERT_FP_LEAK = 3,
  ALERT_RP_LEAK = 4,
  ALERT_TYRE_HIGH_TEMP = 5,
  ALERT_FP_HIGH_PRESSURE = 6,
  ALERT_RP_HIGH_PRESSURE = 7,
  ALERT_FP_LOW_PRESSURE = 8,
  ALERT_RP_LOW_PRESSURE = 9,
  ALERT_FALL = 10,
  ALERT_CRASH = 11,
  ALERT_TOPPLE = 12,
  ALERT_GUARD_DANGEROUS = 13,
  ALERT_GUARD_COMMON = 14,
  ALERT_PARKING = 15,
  ALERT_MOVING = 16,
  ALERT_RAPID_ACCELERATION = 17,
  ALERT_IN_FENCE = 18,
  ALERT_OUT_FENCE = 19,
  AlertItem_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  AlertItem_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool AlertItem_IsValid(int value);
constexpr AlertItem AlertItem_MIN = UNKNOWN;
constexpr AlertItem AlertItem_MAX = ALERT_OUT_FENCE;
constexpr int AlertItem_ARRAYSIZE = AlertItem_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* AlertItem_descriptor();
template<typename T>
inline const std::string& AlertItem_Name(T enum_t_value) {
  static_assert(::std::is_same<T, AlertItem>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function AlertItem_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    AlertItem_descriptor(), enum_t_value);
}
inline bool AlertItem_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, AlertItem* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<AlertItem>(
    AlertItem_descriptor(), name, value);
}
// ===================================================================

class Alert final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:AlertNS.Alert) */ {
 public:
  inline Alert() : Alert(nullptr) {}
  ~Alert() override;
  explicit constexpr Alert(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Alert(const Alert& from);
  Alert(Alert&& from) noexcept
    : Alert() {
    *this = ::std::move(from);
  }

  inline Alert& operator=(const Alert& from) {
    CopyFrom(from);
    return *this;
  }
  inline Alert& operator=(Alert&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Alert& default_instance() {
    return *internal_default_instance();
  }
  static inline const Alert* internal_default_instance() {
    return reinterpret_cast<const Alert*>(
               &_Alert_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Alert& a, Alert& b) {
    a.Swap(&b);
  }
  inline void Swap(Alert* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Alert* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Alert* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Alert>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Alert& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Alert& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Alert* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "AlertNS.Alert";
  }
  protected:
  explicit Alert(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAlertMsgFieldNumber = 1,
    kLocationFieldNumber = 2,
  };
  // repeated .AlertNS.AlertMsg alertMsg = 1;
  int alertmsg_size() const;
  private:
  int _internal_alertmsg_size() const;
  public:
  void clear_alertmsg();
  ::AlertNS::AlertMsg* mutable_alertmsg(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AlertNS::AlertMsg >*
      mutable_alertmsg();
  private:
  const ::AlertNS::AlertMsg& _internal_alertmsg(int index) const;
  ::AlertNS::AlertMsg* _internal_add_alertmsg();
  public:
  const ::AlertNS::AlertMsg& alertmsg(int index) const;
  ::AlertNS::AlertMsg* add_alertmsg();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AlertNS::AlertMsg >&
      alertmsg() const;

  // bytes location = 2;
  void clear_location();
  const std::string& location() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_location(ArgT0&& arg0, ArgT... args);
  std::string* mutable_location();
  PROTOBUF_NODISCARD std::string* release_location();
  void set_allocated_location(std::string* location);
  private:
  const std::string& _internal_location() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_location(const std::string& value);
  std::string* _internal_mutable_location();
  public:

  // @@protoc_insertion_point(class_scope:AlertNS.Alert)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AlertNS::AlertMsg > alertmsg_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr location_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_alert_2eproto;
};
// -------------------------------------------------------------------

class AlertMsg final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:AlertNS.AlertMsg) */ {
 public:
  inline AlertMsg() : AlertMsg(nullptr) {}
  ~AlertMsg() override;
  explicit constexpr AlertMsg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  AlertMsg(const AlertMsg& from);
  AlertMsg(AlertMsg&& from) noexcept
    : AlertMsg() {
    *this = ::std::move(from);
  }

  inline AlertMsg& operator=(const AlertMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline AlertMsg& operator=(AlertMsg&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const AlertMsg& default_instance() {
    return *internal_default_instance();
  }
  static inline const AlertMsg* internal_default_instance() {
    return reinterpret_cast<const AlertMsg*>(
               &_AlertMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(AlertMsg& a, AlertMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(AlertMsg* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(AlertMsg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  AlertMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<AlertMsg>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const AlertMsg& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const AlertMsg& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AlertMsg* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "AlertNS.AlertMsg";
  }
  protected:
  explicit AlertMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kAlertItemFieldNumber = 1,
    kStatusFieldNumber = 2,
  };
  // .AlertNS.AlertItem alertItem = 1;
  void clear_alertitem();
  ::AlertNS::AlertItem alertitem() const;
  void set_alertitem(::AlertNS::AlertItem value);
  private:
  ::AlertNS::AlertItem _internal_alertitem() const;
  void _internal_set_alertitem(::AlertNS::AlertItem value);
  public:

  // bool status = 2;
  void clear_status();
  bool status() const;
  void set_status(bool value);
  private:
  bool _internal_status() const;
  void _internal_set_status(bool value);
  public:

  // @@protoc_insertion_point(class_scope:AlertNS.AlertMsg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  int alertitem_;
  bool status_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_alert_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Alert

// repeated .AlertNS.AlertMsg alertMsg = 1;
inline int Alert::_internal_alertmsg_size() const {
  return alertmsg_.size();
}
inline int Alert::alertmsg_size() const {
  return _internal_alertmsg_size();
}
inline void Alert::clear_alertmsg() {
  alertmsg_.Clear();
}
inline ::AlertNS::AlertMsg* Alert::mutable_alertmsg(int index) {
  // @@protoc_insertion_point(field_mutable:AlertNS.Alert.alertMsg)
  return alertmsg_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AlertNS::AlertMsg >*
Alert::mutable_alertmsg() {
  // @@protoc_insertion_point(field_mutable_list:AlertNS.Alert.alertMsg)
  return &alertmsg_;
}
inline const ::AlertNS::AlertMsg& Alert::_internal_alertmsg(int index) const {
  return alertmsg_.Get(index);
}
inline const ::AlertNS::AlertMsg& Alert::alertmsg(int index) const {
  // @@protoc_insertion_point(field_get:AlertNS.Alert.alertMsg)
  return _internal_alertmsg(index);
}
inline ::AlertNS::AlertMsg* Alert::_internal_add_alertmsg() {
  return alertmsg_.Add();
}
inline ::AlertNS::AlertMsg* Alert::add_alertmsg() {
  ::AlertNS::AlertMsg* _add = _internal_add_alertmsg();
  // @@protoc_insertion_point(field_add:AlertNS.Alert.alertMsg)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::AlertNS::AlertMsg >&
Alert::alertmsg() const {
  // @@protoc_insertion_point(field_list:AlertNS.Alert.alertMsg)
  return alertmsg_;
}

// bytes location = 2;
inline void Alert::clear_location() {
  location_.ClearToEmpty();
}
inline const std::string& Alert::location() const {
  // @@protoc_insertion_point(field_get:AlertNS.Alert.location)
  return _internal_location();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void Alert::set_location(ArgT0&& arg0, ArgT... args) {
 
 location_.SetBytes(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:AlertNS.Alert.location)
}
inline std::string* Alert::mutable_location() {
  std::string* _s = _internal_mutable_location();
  // @@protoc_insertion_point(field_mutable:AlertNS.Alert.location)
  return _s;
}
inline const std::string& Alert::_internal_location() const {
  return location_.Get();
}
inline void Alert::_internal_set_location(const std::string& value) {
  
  location_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* Alert::_internal_mutable_location() {
  
  return location_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* Alert::release_location() {
  // @@protoc_insertion_point(field_release:AlertNS.Alert.location)
  return location_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void Alert::set_allocated_location(std::string* location) {
  if (location != nullptr) {
    
  } else {
    
  }
  location_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), location,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (location_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    location_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:AlertNS.Alert.location)
}

// -------------------------------------------------------------------

// AlertMsg

// .AlertNS.AlertItem alertItem = 1;
inline void AlertMsg::clear_alertitem() {
  alertitem_ = 0;
}
inline ::AlertNS::AlertItem AlertMsg::_internal_alertitem() const {
  return static_cast< ::AlertNS::AlertItem >(alertitem_);
}
inline ::AlertNS::AlertItem AlertMsg::alertitem() const {
  // @@protoc_insertion_point(field_get:AlertNS.AlertMsg.alertItem)
  return _internal_alertitem();
}
inline void AlertMsg::_internal_set_alertitem(::AlertNS::AlertItem value) {
  
  alertitem_ = value;
}
inline void AlertMsg::set_alertitem(::AlertNS::AlertItem value) {
  _internal_set_alertitem(value);
  // @@protoc_insertion_point(field_set:AlertNS.AlertMsg.alertItem)
}

// bool status = 2;
inline void AlertMsg::clear_status() {
  status_ = false;
}
inline bool AlertMsg::_internal_status() const {
  return status_;
}
inline bool AlertMsg::status() const {
  // @@protoc_insertion_point(field_get:AlertNS.AlertMsg.status)
  return _internal_status();
}
inline void AlertMsg::_internal_set_status(bool value) {
  
  status_ = value;
}
inline void AlertMsg::set_status(bool value) {
  _internal_set_status(value);
  // @@protoc_insertion_point(field_set:AlertNS.AlertMsg.status)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace AlertNS

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::AlertNS::AlertItem> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::AlertNS::AlertItem>() {
  return ::AlertNS::AlertItem_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_alert_2eproto
