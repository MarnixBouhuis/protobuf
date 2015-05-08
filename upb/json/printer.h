/*
 * upb - a minimalist implementation of protocol buffers.
 *
 * Copyright (c) 2014 Google Inc.  See LICENSE for details.
 * Author: Josh Haberman <jhaberman@gmail.com>
 *
 * upb::json::Printer allows you to create handlers that emit JSON
 * according to a specific protobuf schema.
 */

#ifndef UPB_JSON_TYPED_PRINTER_H_
#define UPB_JSON_TYPED_PRINTER_H_

#include "upb/env.h"
#include "upb/sink.h"

#ifdef __cplusplus
namespace upb {
namespace json {
class Printer;
}  // namespace json
}  // namespace upb
#endif

UPB_DECLARE_TYPE(upb::json::Printer, upb_json_printer);


/* upb::json::Printer *********************************************************/

#define UPB_JSON_PRINTER_SIZE 168

#ifdef __cplusplus

// Prints an incoming stream of data to a BytesSink in JSON format.
class upb::json::Printer {
 public:
  static Printer* Create(Environment* env, const upb::Handlers* handlers,
                         BytesSink* output);

  // The input to the printer.
  Sink* input();

  // Returns handlers for printing according to the specified schema.
  static reffed_ptr<const Handlers> NewHandlers(const upb::MessageDef* md);

  static const size_t kSize = UPB_JSON_PRINTER_SIZE;

 private:
  UPB_DISALLOW_POD_OPS(Printer, upb::json::Printer);
};

#endif

UPB_BEGIN_EXTERN_C

// Native C API.
upb_json_printer *upb_json_printer_create(upb_env *e, const upb_handlers *h,
                                          upb_bytessink *output);
upb_sink *upb_json_printer_input(upb_json_printer *p);
const upb_handlers *upb_json_printer_newhandlers(const upb_msgdef *md,
                                                 const void *owner);

UPB_END_EXTERN_C

#ifdef __cplusplus

namespace upb {
namespace json {
inline Printer* Printer::Create(Environment* env, const upb::Handlers* handlers,
                                BytesSink* output) {
  return upb_json_printer_create(env, handlers, output);
}
inline Sink* Printer::input() { return upb_json_printer_input(this); }
inline reffed_ptr<const Handlers> Printer::NewHandlers(
    const upb::MessageDef *md) {
  const Handlers* h = upb_json_printer_newhandlers(md, &h);
  return reffed_ptr<const Handlers>(h, &h);
}
}  // namespace json
}  // namespace upb

#endif

#endif  // UPB_JSON_TYPED_PRINTER_H_
