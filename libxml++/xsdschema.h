/* Copyright (C) 2014 The libxml++ development team
 *
 * This file is part of libxml++.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBXMLPP_XSDSCHEMA_H
#define __LIBXMLPP_XSDSCHEMA_H

#include <libxml++/schemabase.h>
#include <libxml++/document.h>
#include <memory> // std::unique_ptr

#ifndef DOXYGEN_SHOULD_SKIP_THIS
extern "C" {
  struct _xmlSchema;
  struct _xmlSchemaParserCtxt;
}
#endif //DOXYGEN_SHOULD_SKIP_THIS

namespace xmlpp
{

/** Represents an XSD schema for validating XML files.
 * XSD = XML %Schema Definition, a.k.a. XML %Schema or W3C XML %Schema
 *
 * @newin{2,38}
 */
class XsdSchema : public SchemaBase
{
public:
  LIBXMLPP_API XsdSchema();

  /** Create a schema from the underlying libxml schema element.
   * @param schema A pointer to the libxml schema element. The XsdSchema takes
   *               ownership of the _xmlSchema. The caller must not deallocate it.
   */
  LIBXMLPP_API
  explicit XsdSchema(_xmlSchema* schema);

  /** Create a schema from a schema definition file.
   * @param filename The URL of the schema.
   * @throws xmlpp::parse_error
   */
  LIBXMLPP_API
  explicit XsdSchema(const std::string& filename);

  /** Create a schema from an XML document.
   * @param document A preparsed document tree, containing the schema definition.
   * @throws xmlpp::parse_error
   */
  LIBXMLPP_API
  explicit XsdSchema(const Document* document);

  LIBXMLPP_API ~XsdSchema() override;

  /** Parse a schema definition file.
   * If another schema has been parsed before, that schema is replaced by the new one.
   * @param filename The URL of the schema.
   * @throws xmlpp::parse_error
   */
  LIBXMLPP_API
  void parse_file(const std::string& filename) override;

  /** Parse a schema definition from a string.
   * If another schema has been parsed before, that schema is replaced by the new one.
   * @param contents The schema definition as a string.
   * @throws xmlpp::parse_error
   */
  LIBXMLPP_API
  void parse_memory(const ustring& contents) override;

  /** Parse a schema definition from a document.
   * If another schema has been parsed before, that schema is replaced by the new one.
   * @param document A preparsed document tree, containing the schema definition.
   * @throws xmlpp::parse_error
   */
  LIBXMLPP_API
  void parse_document(const Document* document) override;

  /** Access the underlying libxml implementation. */
  LIBXMLPP_API _xmlSchema* cobj() noexcept;

  /** Access the underlying libxml implementation. */
  LIBXMLPP_API const _xmlSchema* cobj() const noexcept;

protected:
  LIBXMLPP_API
  void release_underlying();
  LIBXMLPP_API
  void parse_context(_xmlSchemaParserCtxt* context);

private:
  struct Impl;
  std::unique_ptr<Impl> pimpl_;
};

} // namespace xmlpp

#endif //__LIBXMLPP_XSDSCHEMA_H
