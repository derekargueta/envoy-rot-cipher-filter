// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rot_cipher.proto

#ifndef PROTOBUF_rot_5fcipher_2eproto__INCLUDED
#define PROTOBUF_rot_5fcipher_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_rot_5fcipher_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsRotCipherImpl();
void InitDefaultsRotCipher();
inline void InitDefaults() {
  InitDefaultsRotCipher();
}
}  // namespace protobuf_rot_5fcipher_2eproto
namespace example {
class RotCipher;
class RotCipherDefaultTypeInternal;
extern RotCipherDefaultTypeInternal _RotCipher_default_instance_;
}  // namespace example
namespace example {

// ===================================================================

class RotCipher : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:example.RotCipher) */ {
 public:
  RotCipher();
  virtual ~RotCipher();

  RotCipher(const RotCipher& from);

  inline RotCipher& operator=(const RotCipher& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RotCipher(RotCipher&& from) noexcept
    : RotCipher() {
    *this = ::std::move(from);
  }

  inline RotCipher& operator=(RotCipher&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const RotCipher& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RotCipher* internal_default_instance() {
    return reinterpret_cast<const RotCipher*>(
               &_RotCipher_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(RotCipher* other);
  friend void swap(RotCipher& a, RotCipher& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RotCipher* New() const PROTOBUF_FINAL { return New(NULL); }

  RotCipher* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const RotCipher& from);
  void MergeFrom(const RotCipher& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(RotCipher* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string rot_header = 2;
  void clear_rot_header();
  static const int kRotHeaderFieldNumber = 2;
  const ::std::string& rot_header() const;
  void set_rot_header(const ::std::string& value);
  #if LANG_CXX11
  void set_rot_header(::std::string&& value);
  #endif
  void set_rot_header(const char* value);
  void set_rot_header(const char* value, size_t size);
  ::std::string* mutable_rot_header();
  ::std::string* release_rot_header();
  void set_allocated_rot_header(::std::string* rot_header);

  // int32 rot_value = 1;
  void clear_rot_value();
  static const int kRotValueFieldNumber = 1;
  ::google::protobuf::int32 rot_value() const;
  void set_rot_value(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:example.RotCipher)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr rot_header_;
  ::google::protobuf::int32 rot_value_;
  mutable int _cached_size_;
  friend struct ::protobuf_rot_5fcipher_2eproto::TableStruct;
  friend void ::protobuf_rot_5fcipher_2eproto::InitDefaultsRotCipherImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RotCipher

// int32 rot_value = 1;
inline void RotCipher::clear_rot_value() {
  rot_value_ = 0;
}
inline ::google::protobuf::int32 RotCipher::rot_value() const {
  // @@protoc_insertion_point(field_get:example.RotCipher.rot_value)
  return rot_value_;
}
inline void RotCipher::set_rot_value(::google::protobuf::int32 value) {
  
  rot_value_ = value;
  // @@protoc_insertion_point(field_set:example.RotCipher.rot_value)
}

// string rot_header = 2;
inline void RotCipher::clear_rot_header() {
  rot_header_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RotCipher::rot_header() const {
  // @@protoc_insertion_point(field_get:example.RotCipher.rot_header)
  return rot_header_.GetNoArena();
}
inline void RotCipher::set_rot_header(const ::std::string& value) {
  
  rot_header_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:example.RotCipher.rot_header)
}
#if LANG_CXX11
inline void RotCipher::set_rot_header(::std::string&& value) {
  
  rot_header_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:example.RotCipher.rot_header)
}
#endif
inline void RotCipher::set_rot_header(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  rot_header_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:example.RotCipher.rot_header)
}
inline void RotCipher::set_rot_header(const char* value, size_t size) {
  
  rot_header_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:example.RotCipher.rot_header)
}
inline ::std::string* RotCipher::mutable_rot_header() {
  
  // @@protoc_insertion_point(field_mutable:example.RotCipher.rot_header)
  return rot_header_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RotCipher::release_rot_header() {
  // @@protoc_insertion_point(field_release:example.RotCipher.rot_header)
  
  return rot_header_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RotCipher::set_allocated_rot_header(::std::string* rot_header) {
  if (rot_header != NULL) {
    
  } else {
    
  }
  rot_header_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), rot_header);
  // @@protoc_insertion_point(field_set_allocated:example.RotCipher.rot_header)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace example

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_rot_5fcipher_2eproto__INCLUDED