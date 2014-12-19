/*
 * Copyright 2005-2014 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
 * virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
 */

/*! \file eccodes.h
  \brief eccodes C header file

  This is the only file that must be included to use the eccodes library
  from C.
*/

#ifndef eccodes_H
#define eccodes_H

#ifdef __cplusplus
extern "C" {
#endif

#include "grib_api.h"

#define CODES_VERSION GRIB_API_VERSION

/* LOG MODES
Log mode for information for processing information
*/
#define CODES_LOG_INFO    GRIB_LOG_INFO
#define CODES_LOG_WARNING GRIB_LOG_WARNING
#define CODES_LOG_ERROR   GRIB_LOG_ERROR
#define CODES_LOG_FATAL   GRIB_LOG_FATAL
#define CODES_LOG_DEBUG   GRIB_LOG_DEBUG

/* Types */
#define CODES_TYPE_UNDEFINED GRIB_TYPE_UNDEFINED
#define CODES_TYPE_LONG      GRIB_TYPE_LONG
#define CODES_TYPE_DOUBLE    GRIB_TYPE_DOUBLE
#define CODES_TYPE_STRING    GRIB_TYPE_STRING
#define CODES_TYPE_BYTES     GRIB_TYPE_BYTES
#define CODES_TYPE_SECTION   GRIB_TYPE_SECTION
#define CODES_TYPE_LABEL     GRIB_TYPE_LABEL
#define CODES_TYPE_MISSING   GRIB_TYPE_MISSING

/* Missing values */
#define CODES_MISSING_LONG   GRIB_MISSING_LONG
#define CODES_MISSING_DOUBLE GRIB_MISSING_DOUBLE

/*set spec flags*/
#define CODES_UTIL_SET_SPEC_FLAGS_ONLY_PACKING GRIB_UTIL_SET_SPEC_FLAGS_ONLY_PACKING

/* Dump option flags*/
#define CODES_DUMP_FLAG_READ_ONLY    GRIB_DUMP_FLAG_READ_ONLY   
#define CODES_DUMP_FLAG_DUMP_OK      GRIB_DUMP_FLAG_DUMP_OK     
#define CODES_DUMP_FLAG_VALUES       GRIB_DUMP_FLAG_VALUES      
#define CODES_DUMP_FLAG_CODED        GRIB_DUMP_FLAG_CODED       
#define CODES_DUMP_FLAG_OCTECT       GRIB_DUMP_FLAG_OCTECT      
#define CODES_DUMP_FLAG_ALIASES      GRIB_DUMP_FLAG_ALIASES     
#define CODES_DUMP_FLAG_TYPE         GRIB_DUMP_FLAG_TYPE        
#define CODES_DUMP_FLAG_HEXADECIMAL  GRIB_DUMP_FLAG_HEXADECIMAL 
#define CODES_DUMP_FLAG_NO_DATA      GRIB_DUMP_FLAG_NO_DATA     
#define CODES_DUMP_FLAG_ALL_DATA     GRIB_DUMP_FLAG_ALL_DATA     

/* grib_nearest flags */
#define CODES_NEAREST_SAME_GRID   GRIB_NEAREST_SAME_GRID  
#define CODES_NEAREST_SAME_DATA   GRIB_NEAREST_SAME_DATA  
#define CODES_NEAREST_SAME_POINT  GRIB_NEAREST_SAME_POINT 

/*! Iteration is carried out on all the keys available in the message
\ingroup keys_iterator
\see codes_keys_iterator_new
*/
#define CODES_KEYS_ITERATOR_ALL_KEYS  GRIB_KEYS_ITERATOR_ALL_KEYS

/*! read only keys are skipped by keys iterator.
\ingroup keys_iterator
\see codes_keys_iterator_new
*/
#define CODES_KEYS_ITERATOR_SKIP_READ_ONLY  GRIB_KEYS_ITERATOR_SKIP_READ_ONLY

/*! optional keys are skipped by keys iterator.
\ingroup keys_iterator
\see codes_keys_iterator_new */
#define CODES_KEYS_ITERATOR_SKIP_OPTIONAL  GRIB_KEYS_ITERATOR_SKIP_OPTIONAL

/*! edition specific keys are skipped by keys iterator.
\ingroup keys_iterator
\see codes_keys_iterator_new */
#define CODES_KEYS_ITERATOR_SKIP_EDITION_SPECIFIC  GRIB_KEYS_ITERATOR_SKIP_EDITION_SPECIFIC

/*! coded keys are skipped by keys iterator.
\ingroup keys_iterator
\see codes_keys_iterator_new */
#define CODES_KEYS_ITERATOR_SKIP_CODED  GRIB_KEYS_ITERATOR_SKIP_CODED

/*! computed keys are skipped by keys iterator.
\ingroup keys_iterator
\see codes_keys_iterator_new */
#define CODES_KEYS_ITERATOR_SKIP_COMPUTED  GRIB_KEYS_ITERATOR_SKIP_COMPUTED

/*! duplicates of a key are skipped by keys iterator.
\ingroup keys_iterator
\see codes_keys_iterator_new */
#define CODES_KEYS_ITERATOR_SKIP_DUPLICATES  GRIB_KEYS_ITERATOR_SKIP_DUPLICATES

/*! function keys are skipped by keys iterator.
\ingroup keys_iterator
\see codes_keys_iterator_new */
#define CODES_KEYS_ITERATOR_SKIP_FUNCTION   GRIB_KEYS_ITERATOR_SKIP_FUNCTION


grib_fieldset *codes_fieldset_new_from_files(grib_context *c, char *filenames[], int nfiles, char **keys, int nkeys, char *where_string, char *order_by_string, int *err);

void codes_fieldset_delete(grib_fieldset* set);
void codes_fieldset_rewind(grib_fieldset* set);
int  codes_fieldset_apply_order_by(grib_fieldset* set,const char* order_by_string);
grib_handle* codes_fieldset_next_handle(grib_fieldset* set,int* err);
int  codes_fieldset_count(grib_fieldset *set);
int  codes_values_check(grib_handle* h, grib_values* values, int count);

/*! \defgroup grib_index The grib_index
The grib_index is the structure giving indexed access to messages in a file.
 */
/*! @{*/

/**
 *  Create a new index form a file. The file is indexed with the keys in argument.
 *
 * @param c           : context  (NULL for default context)
 * @param filename    : name of the file of messages to be indexed
 * @param keys        : comma separated list of keys for the index.
 *    The type of the key can be explicitly declared appending :l for long,
 *    :d for double, :s for string to the key name. If the type is not
 *    declared explicitly, the native type is assumed.
 * @param err         :  0 if OK, integer value on error
 * @return            the newly created index
 */
grib_index* codes_index_new_from_file(grib_context* c, char* filename,const char* keys,int *err);

/**
 *  Create a new index based on a set of keys.
 *
 * @param c           : context  (NULL for default context)
 * @param keys        : comma separated list of keys for the index.
 *    The type of the key can be explicitly declared appending :l for long,
 *    :d for double, :s for string to the key name. If the type is not
 *    declared explicitly, the native type is assumed.
 * @param err         :  0 if OK, integer value on error
 * @return            the newly created index
 */
grib_index* codes_index_new(grib_context* c, const char* keys,int *err);

/**
 *  Indexes the file given in argument in the index given in argument. 
 *
 * @param index       : index
 * @param filename    : name of the file of messages to be indexed
 * @return            0 if OK, integer value on error
 */
int codes_index_write(grib_index *index, const char *filename);
grib_index* codes_index_read(grib_context* c,const char* filename,int *err);

/**
 *  Get the number of distinct values of the key in argument contained in the index. The key must belong to the index.
 *
 * @param index       : an index created from a file.
 *     The index must have been created with the key in argument.
 * @param key         : key for which the number of values is computed
 * @param size        : number of distinct values of the key in the index
 * @return            0 if OK, integer value on error
 */
int codes_index_get_size(grib_index* index,const char* key,size_t* size);

/**
 *  Get the distinct values of the key in argument contained in the index. The key must belong to the index. This function is used when the type of the key was explicitly defined as long or when the native type of the key is long.
 *
 * @param index       : an index created from a file.
 *     The index must have been created with the key in argument.
 * @param key         : key for which the values are returned
 * @param values      : array of values. The array must be allocated before entering this function and its size must be enough to contain all the values.
 * @param size        : size of the values array
 * @return            0 if OK, integer value on error
 */
int codes_index_get_long(grib_index* index,const char* key,long* values,size_t *size);

/**
 *  Get the distinct values of the key in argument contained in the index. The key must belong to the index. This function is used when the type of the key was explicitly defined as double or when the native type of the key is double.
 *
 * @param index       : an index created from a file.
 *     The index must have been created with the key in argument.
 * @param key         : key for which the values are returned
 * @param values      : array of values. The array must be allocated before entering this function and its size must be enough to contain all the values.
 * @param size        : size of the values array
 * @return            0 if OK, integer value on error
 */
int codes_index_get_double(grib_index* index,const char* key, double* values,size_t *size);

/**
 *  Get the distinct values of the key in argument contained in the index. The key must belong to the index. This function is used when the type of the key was explicitly defined as string or when the native type of the key is string.
 *
 * @param index       : an index created from a file.
 *     The index must have been created with the key in argument.
 * @param key         : key for which the values are returned
 * @param values      : array of values. The array must be allocated before entering this function and its size must be enough to contain all the values.
 * @param size        : size of the values array
 * @return            0 if OK, integer value on error
 */
int codes_index_get_string(grib_index* index,const char* key,char** values,size_t *size);


/**
 *  Select the message subset with key==value. The value is a long. The key must have been created with long type or have long as native type if the type was not explicitly defined in the index creation.
 *
 * @param index       : an index created from a file.
 *     The index must have been created with the key in argument.
 * @param key         : key to be selected
 * @param value       : value of the key to select
 * @return            0 if OK, integer value on error
 */
int codes_index_select_long(grib_index* index,const char* key,long value);

/**
 *  Select the message subset with key==value. The value is a double. The key must have been created with double type or have double as native type if the type was not explicitly defined in the index creation.
 *
 * @param index       : an index created from a file.
 *     The index must have been created with the key in argument.
 * @param key         : key to be selected
 * @param value       : value of the key to select
 * @return            0 if OK, integer value on error
 */
int codes_index_select_double(grib_index* index,const char* key,double value);

/**
 *  Select the message subset with key==value. The value is a string. The key must have been created with string type or have string as native type if the type was not explicitly defined in the index creation.
 *
 * @param index       : an index created from a file.
 *     The index must have been created with the key in argument.
 * @param key         : key to be selected
 * @param value       : value of the key to select
 * @return            0 if OK, integer value on error
 */
int codes_index_select_string(grib_index* index,const char* key,char* value);

/**
 *  Create a new handle from an index after having selected the key values.
 *  All the keys belonging to the index must be selected before calling this function. Successive calls to this function will return all the handles compatible with the constraints defined selecting the values of the index keys.
 * When no more handles are available from the index a NULL pointer is returned and the err variable is set to GRIB_END_OF_INDEX.
 *
 * @param index       : an index created from a file.
 * @param err         :  0 if OK, integer value on error. GRIB_END_OF_INDEX when no more handles are contained in the index.
 * @return            grib handle.
 */
grib_handle* codes_handle_new_from_index(grib_index* index,int *err);

/**
 *  Delete the index.
 *
 * @param index       : index to be deleted.
 */
void codes_index_delete(grib_index* index);

/*! @} */

/*! \defgroup grib_handle The grib_handle
The grib_handle is the structure giving access to parsed grib values by keys.
*/
/*! @{*/
/**
*  Counts the messages contained in a file resource.
*
* @param c           : the context from which the handle will be created (NULL for default context)
* @param f           : the file resource
* @param n           : the number of messages in the file
* @return            0 if OK, integer value on error
*/
int codes_count_in_file(grib_context* c, FILE* f,int* n);

/**
*  Create a handle from a file resource.
*  The file is read until a message is found. The message is then copied.
*  Remember always to delete the handle when it is not needed any more to avoid
*  memory leaks.
*
* @param c           : the context from which the handle will be created (NULL for default context)
* @param f           : the file resource
* @param error       : error code set if the returned handle is NULL and the end of file is not reached
* @return            the new handle, NULL if the resource is invalid or a problem is encountered
*/
grib_handle* codes_handle_new_from_file(grib_context* c, FILE* f, int* error);

/**
*  Write a coded message in a file.     
*
* @param h           : grib_handle to be written
* @param file        : name of the file 
* @param mode        : mode 
* @return            0 if OK, integer value on error
*/
int codes_write_message(grib_handle* h,const char* file,const char* mode);

grib_handle* codes_util_sections_copy(grib_handle* hfrom,grib_handle* hto,int what,int *err);
grib_string_list* codes_util_get_param_id(const char* mars_param);
grib_string_list* codes_util_get_mars_param(const char* param_id);

/**
*  Create a handle from a user message in memory. The message will not be freed at the end.
*  The message will be copied as soon as a modification is needed.
*
* @param c           : the context from which the handle will be created (NULL for default context)
* @param data        : the actual message
* @param data_len    : the length of the message in number of bytes
* @return            the new handle, NULL if the message is invalid or a problem is encountered
*/
grib_handle* codes_handle_new_from_message(grib_context* c, void* data, size_t data_len);

/**
*  Create a handle from a user message in memory. The message will not be freed at the end.
*  The message will be copied as soon as a modification is needed.
*  This function works also with multi field messages.
*
* @param c           : the context from which the handle will be created (NULL for default context)
* @param data        : the actual message
* @param data_len    : the length of the message in number of bytes
* @param error       : error code
* @return            the new handle, NULL if the message is invalid or a problem is encountered
*/
grib_handle* codes_handle_new_from_multi_message(grib_context* c,void** data,
                                                size_t *data_len,int* error);

/**
*  Create a handle from a user message. The message is copied and will be freed with the handle
*
* @param c           : the context from which the handle will be created (NULL for default context)
* @param data        : the actual message
* @param data_len    : the length of the message in number of bytes
* @return            the new handle, NULL if the message is invalid or a problem is encountered
*/
grib_handle* codes_handle_new_from_message_copy(grib_context* c, const void* data, size_t data_len);


/**
 *  Create a handle from a message contained in a samples directory.
 *  The message is copied at the creation of the handle
 *
 * @param c           : the context from which the handle will be created (NULL for default context)
 * @param res_name    : the resource name
 * @return            the new handle, NULL if the resource is invalid or a problem is encountered
 */
grib_handle* codes_handle_new_from_samples (grib_context* c, const char* res_name)  ;



/**
*  Clone an existing handle using the context of the original handle,
*  The message is copied and reparsed
*
* @param h           : The handle to be cloned
* @return            the new handle, NULL if the message is invalid or a problem is encountered
*/
grib_handle* codes_handle_clone             (grib_handle* h)                 ;

/**
*  Frees a handle, also frees the message if it is not a user message
*  @see  codes_handle_new_from_message
* @param h           : The handle to be deleted
* @return            0 if OK, integer value on error
*/
int   codes_handle_delete   (grib_handle* h);

/**
 *  Create an empty multi field handle.
 *  Remember always to delete the multi handle when it is not needed any more to avoid
 *  memory leaks.
 *
 * @param c           : the context from which the handle will be created (NULL for default context)
 */
grib_multi_handle* codes_multi_handle_new     (grib_context* c);

/**
 *  Append the sections starting with start_section of the message pointed by h at
 *  the end of the multi field handle mh.
 *  Remember always to delete the multi handle when it is not needed any more to avoid
 *  memory leaks.
 *
 * @param h           : The handle from which the sections are copied.
 * @param start_section : section number. Starting from this section all the sections to the end of the message will be copied.
 * @param mh           : The multi field handle on which the sections are appended.
 * @return            0 if OK, integer value on error
 */
int codes_multi_handle_append(grib_handle* h,int start_section,grib_multi_handle* mh);

/**
 * Delete multi field handle.
 *
 * @param mh           : The multi field handle to be deleted.
 * @return            0 if OK, integer value on error
 */
int codes_multi_handle_delete(grib_multi_handle* mh);

/**
 *  Write a multi field handle in a file.
 *  Remember always to delete the multi handle when it is not needed any more to avoid
 *  memory leaks.
 *
 * @param mh           : The multi field handle to be written.
 * @param f            : File on which the file handle is written.
 * @return            0 if OK, integer value on error
 */
int codes_multi_handle_write(grib_multi_handle* mh,FILE* f);

/*! @} */

/*! \defgroup handling_coded_messages Handling coded messages */
/*! @{ */
/**
* getting the message attached to a handle
*
* @param h              : the grib handle to which the buffer should be gathered
* @param message        : the pointer to be set to the handle's data
* @param message_length : On exit, the message size in number of bytes
* @return            0 if OK, integer value on error
*/
int codes_get_message(grib_handle* h ,const void** message, size_t *message_length  );


/**
* getting a copy of the message attached to a handle
*
* @param h              : the grib handle to which the buffer should be returned
* @param message        : the pointer to the data buffer to be filled
* @param message_length : On entry, the size in number of bytes of the allocated empty message.
*                         On exit, the actual message length in number of bytes
* @return            0 if OK, integer value on error
*/
int codes_get_message_copy(grib_handle* h ,  void* message,size_t *message_length );
/*! @} */

/*! \defgroup iterators Iterating on latitude/longitude/values */
/*! @{ */

/*!
* \brief Create a new iterator from a handle, using current geometry and values.
*
* \param h           : the handle from which the iterator will be created
* \param flags       : flags for future use.
* \param error       : error code
* \return            the new iterator, NULL if no iterator can be created
*/
grib_iterator* codes_iterator_new(grib_handle*   h, unsigned long flags,int* error);

/**
* Get latitude/longitude and data values.
* The Latitudes, longitudes and values arrays must be properly allocated by the caller.
* Their required dimension can be obtained by getting the value of the integer key "numberOfPoints".
*
* @param h           : handle from which geography and data values are taken
* @param lats        : returned array of latitudes
* @param lons        : returned array of longitudes
* @param values      : returned array of data values
* @return            0 if OK, integer value on error
*/
int codes_get_data(grib_handle *h, double *lats, double *lons, double *values, size_t *size);

/**
* Get the next value from an iterator.
*
* @param i           : the iterator
* @param lat         : on output latitude in degree
* @param lon         : on output longitude in degree
* @param value       : on output value of the point
* @return            positive value if successful, 0 if no more data are available
*/
int codes_iterator_next(grib_iterator *i, double* lat,double* lon,double* value);

/**
* Get the previous value from an iterator.
*
* @param i           : the iterator
* @param lat         : on output latitude in degree
* @param lon         : on output longitude in degree
* @param value       : on output value of the point*
* @return            positive value if successful, 0 if no more data are available
*/
int codes_iterator_previous(grib_iterator *i, double* lat,double* lon,double* value);

/**
* Test procedure for values in an iterator.
*
* @param i           : the iterator
* @return            boolean, 1 if the iterator still nave next values, 0 otherwise
*/
int codes_iterator_has_next(grib_iterator *i);

/**
* Test procedure for values in an iterator.
*
* @param i           : the iterator
* @return            0 if OK, integer value on error
*/
int codes_iterator_reset(grib_iterator *i);

/**
*  Frees an iterator from memory
*
* @param i           : the iterator
* @return            0 if OK, integer value on error
*/
int codes_iterator_delete(grib_iterator *i);

/*!
* \brief Create a new nearest from a handle, using current geometry .
*
* \param h           : the handle from which the iterator will be created
* \param error       : error code
* \return            the new nearest, NULL if no nearest can be created
*/
grib_nearest* codes_nearest_new(grib_handle*   h, int* error);

/**
* Find the 4 nearest points of a latitude longitude point.
* The flags are provided to speed up the process of searching. If you are
* sure that the point you are asking for is not changing from a call
* to another you can use GRIB_NEAREST_SAME_POINT. The same is valid for
* the grid. Flags can be used together doing a bitwise OR.
* The distances are given in kilometres.
*
* @param nearest     : nearest structure
* @param h           : handle from which geography and data values are taken
* @param inlat       : latitude of the point to search for
* @param inlon       : longitude of the point to search for
* @param flags       : GRIB_NEAREST_SAME_POINT, GRIB_NEAREST_SAME_GRID
* @param outlats     : returned array of latitudes of the nearest points
* @param outlons     : returned array of longitudes of the nearest points
* @param values      : returned array of data values of the nearest points
* @param distances   : returned array of distances from the nearest points
* @param indexes     : returned array of indexes of the nearest points
* @param len         : size of the arrays
* @return            0 if OK, integer value on error
*/
int codes_nearest_find(grib_nearest *nearest,grib_handle* h,double inlat,double inlon,
    unsigned long flags,double* outlats,double* outlons,
    double* values,double* distances,int* indexes,size_t *len);

/**
*  Frees an nearest from memory
*
* @param nearest           : the nearest
* @return            0 if OK, integer value on error
*/
int codes_nearest_delete(grib_nearest *nearest);

/**
* Find the nearest point of a set of points whose latitudes and longitudes
* are given in the inlats, inlons arrays respectively.
* If the flag is_lsm is 1 the nearest land point is returned and the
* grib passed as handle (h) is considered a land sea mask.
* The land nearest point is the nearest point with land sea mask value>=0.5.
* If no nearest land points are found the nearest value is returned.
* If the flag is_lsm is 0 the nearest point is returned.
* values, distances, indexes (in the "values" array) for the nearest points (ilons,ilats)
* are returned.
* The distances are given in kilometres.
*
* @param h           : handle from which geography and data values are taken
* @param is_lsm      : lsm flag (1-> nearest land, 0-> nearest)
* @param inlats      : latitudes of the points to search for
* @param inlons      : longitudes of the points to search for
* @param npoints     : number of points (size of the inlats,inlons,outlats,outlons,values,distances,indexes arrays)
* @param outlats     : returned array of latitudes of the nearest points
* @param outlons     : returned array of longitudes of the nearest points
* @param values      : returned array of data values of the nearest points
* @param distances   : returned array of distances from the nearest points
* @param indexes     : returned array of indexes of the nearest points
* @return            0 if OK, integer value on error
*/
int codes_nearest_find_multiple(grib_handle* h,int is_lsm,
    double* inlats,double* inlons,long npoints,
    double* outlats,double* outlons,
    double* values,double* distances, int* indexes);

/* @} */

/*! \defgroup get_set Accessing header and data values   */
/*! @{ */
/**
*  Get the number offset of a key, in a message if several keys of the same name
*  are present, the offset of the last one is returned
*
* @param h           : the handle to get the offset from
* @param key         : the key to be searched
* @param offset      : the address of a size_t where the offset will be set
* @return            0 if OK, integer value on error
*/
int codes_get_offset(grib_handle* h, const char* key, size_t* offset);

/**
*  Get the number of coded value from a key, if several keys of the same name are present, the total sum is returned
*
* @param h           : the handle to get the offset from
* @param key         : the key to be searched
* @param size        : the address of a size_t where the size will be set
* @return            0 if OK, integer value on error
*/
int codes_get_size(grib_handle* h, const char* key,size_t *size);

/**
*  Get the length of the string representation of the key, if several keys of the same name are present, the maximum length is returned
*
* @param h           : the handle to get the offset from
* @param key         : the key to be searched
* @param length        : the address of a size_t where the length will be set
* @return            0 if OK, integer value on error
*/
int codes_get_length(grib_handle* h, const char* key,size_t *length);

/**
*  Get a long value from a key, if several keys of the same name are present, the last one is returned
*  @see  codes_set_long
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param value       : the address of a long where the data will be retrieved
* @return            0 if OK, integer value on error
*/
int codes_get_long(grib_handle* h, const char* key, long*   value  );

/**
*  Get a double value from a key, if several keys of the same name are present, the last one is returned
*  @see  codes_set_double
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param value       : the address of a double where the data will be retrieved
* @return            0 if OK, integer value on error
*/
int codes_get_double(grib_handle* h, const char* key, double* value                             );

/**
*  Get as double the i-th element of the "key" array
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param i           : zero based index
* @param value       : the address of a double where the data will be retrieved
* @return            0 if OK, integer value on error
*/
int codes_get_double_element(grib_handle* h, const char* key, int i, double* value);

/**
*  Get as double array the elements of the "key" array whose indexes are listed in the input array i
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param i           : zero based array of indexes
* @param size        : size of the i and value arrays
* @param value       : the address of a double where the data will be retrieved
* @return            0 if OK, integer value on error
*/
int codes_get_double_elements(grib_handle* h, const char* key, int* i, long size,double* value);

/**
*  Get a string value from a key, if several keys of the same name are present, the last one is returned
* @see  codes_set_string
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param mesg       : the address of a string where the data will be retrieved
* @param length      : the address of a size_t that contains allocated length of the string on input, and that contains the actual length of the string on output
* @return            0 if OK, integer value on error
*/
int codes_get_string(grib_handle* h, const char* key, char* mesg, size_t *length  );

int codes_get_string_array(grib_handle* h, const char* name, char** val, size_t *length);

/**
*  Get raw bytes values from a key. If several keys of the same name are present, the last one is returned
* @see  codes_set_bytes
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param bytes       : the address of a byte array where the data will be retrieved
* @param length      : the address of a size_t that contains allocated length of the byte array on input, and that contains the actual length of the byte array on output
* @return            0 if OK, integer value on error
*/
int codes_get_bytes(grib_handle* h, const char* key, unsigned char* bytes, size_t *length);

/**
*  Get double array values from a key. If several keys of the same name are present, the last one is returned
* @see  codes_set_double_array
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param vals       : the address of a double array where the data will be retrieved
* @param length      : the address of a size_t that contains allocated length of the double array on input, and that contains the actual length of the double array on output
* @return            0 if OK, integer value on error
*/
int codes_get_double_array(grib_handle* h, const char* key, double* vals, size_t *length);

/**
*  Get long array values from a key. If several keys of the same name are present, the last one is returned
* @see  codes_set_long_array
*
* @param h           : the handle to get the data from
* @param key         : the key to be searched
* @param vals       : the address of a long array where the data will be retrieved
* @param length      : the address of a size_t that contains allocated length of the long array on input, and that contains the actual length of the long array on output
* @return            0 if OK, integer value on error
*/
int codes_get_long_array(grib_handle* h, const char* key, long* vals, size_t *length);


/*   setting      data         */
/**
*  Copy the keys belonging to a given namespace from a source handle to a destination handle
*
*
* @param dest      : destination handle
* @param name      : namespace
* @param src       : source handle
* @return          0 if OK, integer value on error
*/
int codes_copy_namespace(grib_handle* dest, const char* name, grib_handle* src);
  
/**
*  Set a long value from a key. If several keys of the same name are present, the last one is set
*  @see  codes_get_long
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param val         : a long where the data will be read
* @return            0 if OK, integer value on error
*/
int codes_set_long(grib_handle* h, const char* key, long val);

/**
*  Set a double value from a key. If several keys of the same name are present, the last one is set
*  @see  codes_get_double
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param val       : a double where the data will be read
* @return            0 if OK, integer value on error
*/
int codes_set_double(grib_handle* h, const char* key, double val);

/**
*  Set a string value from a key. If several keys of the same name are present, the last one is set
*  @see  codes_get_string
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param mesg       : the address of a string where the data will be read
* @param length      : the address of a size_t that contains the length of the string on input, and that contains the actual packed length of the string on output
* @return            0 if OK, integer value on error
*/
int codes_set_string(grib_handle* h, const char*  key , const char* mesg, size_t *length);

/**
*  Set a bytes array from a key. If several keys of the same name are present, the last one is set
*  @see  codes_get_bytes
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param bytes       : the address of a byte array where the data will be read
* @param length      : the address of a size_t that contains the length of the byte array on input, and that contains the actual packed length of the byte array  on output
* @return            0 if OK, integer value on error
*/
int codes_set_bytes(grib_handle* h, const char*  key, const unsigned char* bytes, size_t *length);

/**
*  Set a double array from a key. If several keys of the same name are present, the last one is set
*   @see  codes_get_double_array
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param vals        : the address of a double array where the data will be read
* @param length      : a size_t that contains the length of the byte array on input
* @return            0 if OK, integer value on error
*/
int codes_set_double_array(grib_handle* h, const char* key, const double* vals, size_t length);

/**
* Same as codes_set_double_array but allows setting of READ-ONLY keys like codedValues.
* Use with great caution!!
*/
int codes_set_force_double_array(grib_handle* h, const char* key, const double* vals, size_t length);


/**
*  Set a long array from a key. If several keys of the same name are present, the last one is set
*  @see  codes_get_long_array
*
* @param h           : the handle to set the data to
* @param key         : the key to be searched
* @param vals        : the address of a long array where the data will be read
* @param length      : a size_t that contains the length of the long array on input
* @return            0 if OK, integer value on error
*/
int codes_set_long_array(grib_handle* h, const char* key, const long* vals, size_t length);
/*! @} */


/**
*  Print all keys, with the context print procedure and dump mode to a resource
*
* @param h            : the handle to be printed
* @param out          : output file handle
* @param mode         : available dump modes are: debug wmo c_code
* @param option_flags : all the GRIB_DUMP_FLAG_x flags can be used
* @param arg          : used to provide a format to output data (experimental)
*/
void codes_dump_content(grib_handle* h,FILE* out,const char* mode, unsigned long option_flags,void* arg);

/**
*  Print all keys from the parsed definition files available in a context
*
* @param f           : the File used to print the keys on
* @param c           : the context that contains the cached definition files to be printed
*/
void codes_dump_action_tree(grib_context* c, FILE* f) ;

/*! \defgroup context The context object
 The context is a long life configuration object of the grib_api.
 It is used to define special allocation and free routines or
 to set special grib_api behaviours and variables.
 */
/*! @{ */

/* TODO: function pointers
 grib_malloc_proc
 grib_realloc_proc
 grib_log_proc
 grib_print_proc
 grib_data_read_proc
 grib_data_write_proc
 grib_data_tell_proc 
 grib_data_seek_proc
 grib_data_eof_proc
*/

/**
*  Get the static default context
*
* @return            the default context, NULL it the context is not available
*/
grib_context* codes_context_get_default(void);

/**
*  Create and allocate a new context from a parent context.
*
* @param c           : the context to be cloned, NULL for default context
* @return            the new and empty context, NULL if error
*/
grib_context* codes_context_new(grib_context* c);

/**
*  Frees the cached definition files of the context
*
* @param c           : the context to be deleted
*/
void codes_context_delete(grib_context* c);

/**
*  Set the GTS header mode on.
*  The GTS headers will be preserved.
*
* @param c           : the context
*/
void codes_gts_header_on(grib_context* c) ;

/**
*  Set the GTS header mode off.
*  The GTS headers will be deleted.
*
* @param c           : the context
*/
void codes_gts_header_off(grib_context* c);

/**
*  Set the GRIBEX mode on.
*  Grib files will be compatible with GRIBEX.
*
* @param c           : the context
*/
void codes_gribex_mode_on(grib_context* c);

/**
*  Get the GRIBEX mode.
*
* @param c           : the context
*/
int codes_get_gribex_mode(grib_context* c);

/**
*  Set the GRIBEX mode off.
*  GRIB files won't be always compatible with GRIBEX.
*
* @param c           : the context
*/
void codes_gribex_mode_off(grib_context* c);

/**
*  Turn on support for multiple fields in single grib messages
*
* @param c            : the context to be modified
*/
void codes_multi_support_on(grib_context* c);

/**
*  Turn off support for multiple fields in single grib messages
*
* @param c            : the context to be modified
*/
void codes_multi_support_off(grib_context* c);

/**
*  Reset file handle in multiple field support mode
*
* @param c            : the context to be modified
* @param f            : the file pointer
*/
void codes_multi_support_reset_file(grib_context* c, FILE* f);

char* codes_samples_path(const grib_context *c);
/*! @} */

/**
*  Get the API version
*
*  @return        API version
*/
long codes_get_api_version(void);

/**
*  Get the Git version control SHA1 identifier
*
*  @return character string with SHA1 identifier
*/
const char* codes_get_git_sha1(void);

/**
*  Prints the API version
*
*
*/
void codes_print_api_version(FILE* out);

/*! \defgroup keys_iterator Iterating on keys names
The keys iterator is designed to get the key names defined in a message.
Key names on which the iteration is carried out can be filtered through their
attributes or by the namespace they belong to.
*/
/*! @{ */
/*! Create a new iterator from a valid and initialised handle.
*  @param h             : the handle whose keys you want to iterate
*  @param filter_flags  : flags to filter out some of the keys through their attributes
*  @param name_space     : if not null the iteration is carried out only on
*                         keys belonging to the namespace passed. (NULL for all the keys)
*  @return              keys iterator ready to iterate through keys according to filter_flags
*                         and namespace
*/
grib_keys_iterator* codes_keys_iterator_new(grib_handle* h,unsigned long filter_flags, char* name_space);

/*! Step to the next iterator.
*  @param kiter         : valid grib_keys_iterator
*  @return              1 if next iterator exists, 0 if no more elements to iterate on
*/
int codes_keys_iterator_next(grib_keys_iterator *kiter);


/*! get the key name from the iterator
*  @param kiter         : valid grib_keys_iterator
*  @return              key name
*/
const char* codes_keys_iterator_get_name(grib_keys_iterator *kiter);

/*! Delete the iterator.
*  @param kiter         : valid grib_keys_iterator
*  @return              0 if OK, integer value on error
*/
int codes_keys_iterator_delete( grib_keys_iterator* kiter);

/*! Rewind the iterator.
*  @param kiter         : valid grib_keys_iterator
*  @return              0 if OK, integer value on error
*/
int codes_keys_iterator_rewind(grib_keys_iterator* kiter);

int codes_keys_iterator_set_flags(grib_keys_iterator *kiter,unsigned long flags);

int codes_keys_iterator_get_long(grib_keys_iterator *kiter, long *v, size_t *len);
int codes_keys_iterator_get_double(grib_keys_iterator *kiter, double *v, size_t *len);
int codes_keys_iterator_get_string(grib_keys_iterator *kiter, char *v, size_t *len);
int codes_keys_iterator_get_bytes(grib_keys_iterator *kiter, unsigned char *v, size_t *len);

/* @} */

void codes_update_sections_lengths(grib_handle* h);


/**
* Convert an error code into a string
* @param code       : the error code
* @return           the error message
*/
const char* codes_get_error_message(int code);
const char* codes_get_type_name(int type);

int codes_get_native_type(grib_handle* h, const char* name,int* type);

void codes_check(const char* call,const char*  file,int line,int e,const char* msg);
#define CODES_CHECK(a,msg)        GRIB_CHECK(a,msg)
#define CODES_CHECK_NOLINE(a,msg) GRIB_CHECK_NOLINE(a,msg)


int codes_set_values(grib_handle* h,grib_values*  grib_values , size_t arg_count);
grib_handle* codes_handle_new_from_partial_message_copy(grib_context* c, const void* data, size_t size);
grib_handle* codes_handle_new_from_partial_message(grib_context* c,void* data, size_t buflen);
int codes_is_missing(grib_handle* h, const char* key, int* err);
int codes_is_defined(grib_handle* h, const char* key);
int codes_set_missing(grib_handle* h, const char* key);
/* The truncation is the Gaussian number (or order) */
int codes_get_gaussian_latitudes(long truncation,double* latitudes);

int codes_julian_to_datetime(double jd, long *year, long *month, long *day, long *hour, long *minute, long *second);
int codes_datetime_to_julian(long year, long month, long day, long hour, long minute, long second, double *jd);
long codes_julian_to_date(long jdate);
long codes_date_to_julian(long ddate);

void codes_get_reduced_row(long pl,double lon_first,double lon_last,long* npoints,long* ilon_first, long* ilon_last );

/* read products */
int codes_get_message_offset ( grib_handle* h,off_t* offset );
int codes_get_message_size ( grib_handle* h,size_t* size );

grib_box* codes_box_new(grib_handle* h,int* error);
grib_points* codes_box_get_points(grib_box *box,double north, double west,double south,double east, int *err);
int codes_points_get_values(grib_handle* h, grib_points* points, double* val);

/* --------------------------------------- */

#define CODES_UTIL_GRID_SPEC_REGULAR_LL GRIB_UTIL_GRID_SPEC_REGULAR_LL
#define CODES_UTIL_GRID_SPEC_ROTATED_LL GRIB_UTIL_GRID_SPEC_ROTATED_LL
#define CODES_UTIL_GRID_SPEC_REGULAR_GG GRIB_UTIL_GRID_SPEC_REGULAR_GG
#define CODES_UTIL_GRID_SPEC_ROTATED_GG GRIB_UTIL_GRID_SPEC_ROTATED_GG
#define CODES_UTIL_GRID_SPEC_REDUCED_GG GRIB_UTIL_GRID_SPEC_REDUCED_GG
#define CODES_UTIL_GRID_SPEC_SH         GRIB_UTIL_GRID_SPEC_SH        
#define CODES_UTIL_GRID_SPEC_REDUCED_LL GRIB_UTIL_GRID_SPEC_REDUCED_LL
#define CODES_UTIL_GRID_SPEC_POLAR_STEREOGRAPHIC GRIB_UTIL_GRID_SPEC_POLAR_STEREOGRAPHIC


#define CODES_UTIL_PACKING_TYPE_SPECTRAL_COMPLEX     GRIB_UTIL_PACKING_TYPE_SPECTRAL_COMPLEX
#define CODES_UTIL_PACKING_TYPE_SPECTRAL_SIMPLE      GRIB_UTIL_PACKING_TYPE_SPECTRAL_SIMPLE
#define CODES_UTIL_PACKING_TYPE_JPEG                 GRIB_UTIL_PACKING_TYPE_JPEG
#define CODES_UTIL_PACKING_TYPE_GRID_COMPLEX         GRIB_UTIL_PACKING_TYPE_GRID_COMPLEX
#define CODES_UTIL_PACKING_TYPE_GRID_SIMPLE          GRIB_UTIL_PACKING_TYPE_GRID_SIMPLE
#define CODES_UTIL_PACKING_TYPE_GRID_SIMPLE_MATRIX   GRIB_UTIL_PACKING_TYPE_GRID_SIMPLE_MATRIX
#define CODES_UTIL_PACKING_TYPE_GRID_SECOND_ORDER    GRIB_UTIL_PACKING_TYPE_GRID_SECOND_ORDER
#define CODES_UTIL_PACKING_SAME_AS_INPUT             GRIB_UTIL_PACKING_SAME_AS_INPUT
#define CODES_UTIL_PACKING_USE_PROVIDED              GRIB_UTIL_PACKING_USE_PROVIDED
#define CODES_UTIL_ACCURACY_SAME_BITS_PER_VALUES_AS_INPUT      GRIB_UTIL_ACCURACY_SAME_BITS_PER_VALUES_AS_INPUT
#define CODES_UTIL_ACCURACY_USE_PROVIDED_BITS_PER_VALUES       GRIB_UTIL_ACCURACY_USE_PROVIDED_BITS_PER_VALUES
#define CODES_UTIL_ACCURACY_SAME_DECIMAL_SCALE_FACTOR_AS_INPUT GRIB_UTIL_ACCURACY_SAME_DECIMAL_SCALE_FACTOR_AS_INPUT
#define CODES_UTIL_ACCURACY_USE_PROVIDED_DECIMAL_SCALE_FACTOR  GRIB_UTIL_ACCURACY_USE_PROVIDED_DECIMAL_SCALE_FACTOR


grib_handle *codes_util_set_spec(grib_handle *h, 
	const grib_util_grid_spec    *grid_spec, 
	const grib_util_packing_spec *packing_spec,  /* NULL for defaults (same as input) */
	int flags,
	const double *data_values, 
	size_t data_values_count, 
	int *err);


/* --------------------------------------- */


#ifdef __cplusplus
}
#endif
#endif
/* This part is automatically generated by ./errors.pl, do not edit */
#ifndef grib_errors_H
#define grib_errors_H
/*! \defgroup errors Error codes
Error codes returned by the grib_api functions.
*/
/*! @{*/
/** No error */
#define GRIB_SUCCESS		0
/** End of resource reached */
#define GRIB_END_OF_FILE		-1
/** Internal error */
#define GRIB_INTERNAL_ERROR		-2
/** Passed buffer is too small */
#define GRIB_BUFFER_TOO_SMALL		-3
/** Function not yet implemented */
#define GRIB_NOT_IMPLEMENTED		-4
/** Missing 7777 at end of message */
#define GRIB_7777_NOT_FOUND		-5
/** Passed array is too small */
#define GRIB_ARRAY_TOO_SMALL		-6
/** File not found */
#define GRIB_FILE_NOT_FOUND		-7
/** Code not found in code table */
#define GRIB_CODE_NOT_FOUND_IN_TABLE		-8
/** Array size mismatch */
#define GRIB_WRONG_ARRAY_SIZE		-9
/** Key/value not found */
#define GRIB_NOT_FOUND		-10
/** Input output problem */
#define GRIB_IO_PROBLEM		-11
/** Message invalid */
#define GRIB_INVALID_MESSAGE		-12
/** Decoding invalid */
#define GRIB_DECODING_ERROR		-13
/** Encoding invalid */
#define GRIB_ENCODING_ERROR		-14
/** Code cannot unpack because of string too small */
#define GRIB_NO_MORE_IN_SET		-15
/** Problem with calculation of geographic attributes */
#define GRIB_GEOCALCULUS_PROBLEM		-16
/** Out of memory */
#define GRIB_OUT_OF_MEMORY		-17
/** Value is read only */
#define GRIB_READ_ONLY		-18
/** Invalid argument */
#define GRIB_INVALID_ARGUMENT		-19
/** Null handle */
#define GRIB_NULL_HANDLE		-20
/** Invalid section number */
#define GRIB_INVALID_SECTION_NUMBER		-21
/** Value cannot be missing */
#define GRIB_VALUE_CANNOT_BE_MISSING		-22
/** Wrong message length */
#define GRIB_WRONG_LENGTH		-23
/** Invalid key type */
#define GRIB_INVALID_TYPE		-24
/** Unable to set step */
#define GRIB_WRONG_STEP		-25
/** Wrong units for step (step must be integer) */
#define GRIB_WRONG_STEP_UNIT		-26
/** Invalid file id */
#define GRIB_INVALID_FILE		-27
/** Invalid grib id */
#define GRIB_INVALID_GRIB		-28
/** Invalid index id */
#define GRIB_INVALID_INDEX		-29
/** Invalid iterator id */
#define GRIB_INVALID_ITERATOR		-30
/** Invalid keys iterator id */
#define GRIB_INVALID_KEYS_ITERATOR		-31
/** Invalid nearest id */
#define GRIB_INVALID_NEAREST		-32
/** Invalid order by */
#define GRIB_INVALID_ORDERBY		-33
/** Missing a key from the fieldset */
#define GRIB_MISSING_KEY		-34
/** The point is out of the grid area */
#define GRIB_OUT_OF_AREA		-35
/** Concept no match */
#define GRIB_CONCEPT_NO_MATCH		-36
/** Hash array no match */
#define GRIB_HASH_ARRAY_NO_MATCH		-37
/** Definitions files not found */
#define GRIB_NO_DEFINITIONS		-38
/** Wrong type while packing */
#define GRIB_WRONG_TYPE		-39
/** End of resource */
#define GRIB_END		-40
/** Unable to code a field without values */
#define GRIB_NO_VALUES		-41
/** Grid description is wrong or inconsistent */
#define GRIB_WRONG_GRID		-42
/** End of index reached */
#define GRIB_END_OF_INDEX		-43
/** Null index */
#define GRIB_NULL_INDEX		-44
/** End of resource reached when reading message */
#define GRIB_PREMATURE_END_OF_FILE		-45
/** An internal array is too small */
#define GRIB_INTERNAL_ARRAY_TOO_SMALL		-46
/** Message is too large for the current architecture */
#define GRIB_MESSAGE_TOO_LARGE		-47
/** Constant field */
#define GRIB_CONSTANT_FIELD		-48
/** Switch unable to find a matching case */
#define GRIB_SWITCH_NO_MATCH		-49
/** Underflow */
#define GRIB_UNDERFLOW		-50
/** Message malformed */
#define GRIB_MESSAGE_MALFORMED		-51
/** Index is corrupted */
#define GRIB_CORRUPTED_INDEX		-52
/** Invalid number of bits per value */
#define GRIB_INVALID_BPV		-53
/** Edition of two messages is different */
#define GRIB_DIFFERENT_EDITION		-54
/** Value is different */
#define GRIB_VALUE_DIFFERENT		-55
/** Invalid key value */
#define GRIB_INVALID_KEY_VALUE		-56
/** String is smaller than requested */
#define GRIB_STRING_TOO_SMALL		-57
/** Wrong type conversion */
#define GRIB_WRONG_CONVERSION		-58
/** Missing BUFR table entry for descriptor */
#define GRIB_MISSING_BUFR_ENTRY		-59
/** Null pointer */
#define GRIB_NULL_POINTER		-60
/*! @}*/
#endif
