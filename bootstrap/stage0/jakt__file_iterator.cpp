#include "jakt__file_iterator.h"
namespace Jakt {
namespace jakt__file_iterator {
ErrorOr<String> jakt__file_iterator::RecursiveFileIterator::debug_description() const { auto builder = MUST(StringBuilder::create());TRY(builder.append("RecursiveFileIterator("));{
JaktInternal::PrettyPrint::ScopedLevelIncrease increase_indent {};
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("extension: "));TRY(builder.appendff("\"{}\", ", extension));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("directory_list: "));TRY(builder.appendff("{}, ", directory_list));
TRY(JaktInternal::PrettyPrint::output_indentation(builder));TRY(builder.append("current_directory: "));TRY(builder.appendff("{}", current_directory));
}
TRY(builder.append(")"));return builder.to_string(); }
ErrorOr<NonnullRefPtr<jakt__file_iterator::RecursiveFileIterator>> jakt__file_iterator::RecursiveFileIterator::make(path::Path const directory,String const extension) {
{
return (TRY((jakt__file_iterator::RecursiveFileIterator::create(extension,(TRY((Array<path::Path>::create_with({directory})))),JaktInternal::OptionalNone()))));
}
}

jakt__file_iterator::RecursiveFileIterator::RecursiveFileIterator(String&& a_extension, JaktInternal::Array<path::Path>&& a_directory_list, JaktInternal::Optional<NonnullRefPtr<unknown_fs::DirectoryIterator>>&& a_current_directory): extension(move(a_extension)), directory_list(move(a_directory_list)), current_directory(move(a_current_directory)){}
ErrorOr<NonnullRefPtr<RecursiveFileIterator>> jakt__file_iterator::RecursiveFileIterator::create(String extension, JaktInternal::Array<path::Path> directory_list, JaktInternal::Optional<NonnullRefPtr<unknown_fs::DirectoryIterator>> current_directory) { auto o = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) RecursiveFileIterator (move(extension), move(directory_list), move(current_directory)))); return o; }
ErrorOr<JaktInternal::Optional<path::Path>> jakt__file_iterator::RecursiveFileIterator::next() {
{
if ((!(((((*this).current_directory)).has_value())))){
if ((((((*this).directory_list)).size()) > static_cast<size_t>(0ULL))){
path::Path const path = (((((*this).directory_list)).pop()).value());
(((*this).current_directory) = TRY((unknown_fs::DirectoryIterator::DirectoryIterator::from_path(path))));
if ((!(((((*this).current_directory)).has_value())))){
return (path);
}
}
else {
return (JaktInternal::OptionalNone());
}

}
JaktInternal::Optional<JaktInternal::Tuple<path::Path,bool>> const next = TRY(((((((*this).current_directory).value()))->next())));
if (((next).has_value())){
path::Path new_path = TRY((((TRY(((((((*this).current_directory).value()))->get_path())))).join((((((next.value())).get<0>())).to_string())))));
if ((((next.value())).get<1>())){
TRY((((((*this).directory_list)).push(new_path))));
return (TRY((((*this).next()))));
}
if ((TRY((((new_path).extension()))) == ((*this).extension))){
return (new_path);
}
else {
return (TRY((((*this).next()))));
}

}
else if ((!(((((*this).directory_list)).is_empty())))){
(((*this).current_directory) = TRY((unknown_fs::DirectoryIterator::DirectoryIterator::from_path((((((*this).directory_list)).pop()).value())))));
return (TRY((((*this).next()))));
}
return (JaktInternal::OptionalNone());
}
}

}
} // namespace Jakt
