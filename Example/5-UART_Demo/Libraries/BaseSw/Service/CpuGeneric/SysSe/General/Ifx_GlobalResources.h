/**
 * \file Ifx_GlobalResources.h
 * \brief Handling of global resources
 *
 * \copyright Copyright (c) 2013 Infineon Technologies AG. All rights reserved.
 *
 * $Date: 2014-02-28 14:15:39 GMT$
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Use of this file is subject to the terms of use agreed between (i) you or 
 * the company in which ordinary course of business you are acting and (ii) 
 * Infineon Technologies AG or its licensees. If and as long as no such 
 * terms of use are agreed, use of this file is subject to following:


 * Boost Software License - Version 1.0 - August 17th, 2003

 * Permission is hereby granted, free of charge, to any person or 
 * organization obtaining a copy of the software and accompanying 
 * documentation covered by this license (the "Software") to use, reproduce,
 * display, distribute, execute, and transmit the Software, and to prepare
 * derivative works of the Software, and to permit third-parties to whom the 
 * Software is furnished to do so, all subject to the following:

 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE 
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.

 *
 * \defgroup library_srvsw_sysse_general_globalresources Global resources
 * This module implements the global resources handling
 * \ingroup library_srvsw_sysse_general
 */

#ifndef IFX_GLOBALRESOURCES_H
#define IFX_GLOBALRESOURCES_H            1

#include "Ifx_Cfg.h"
#include "Cpu/Std/Ifx_Types.h"

#ifndef IFX_CFG_GLOBAL_RESOURCES_ENABLED
#define IFX_CFG_GLOBAL_RESOURCES_ENABLED (0)
#endif

typedef struct
{
    void *resource;
    pchar name;
} Ifx_GlobalResources_Item;

/** \addtogroup library_srvsw_sysse_general_globalresources
 * \{ */
/** Return a pointer to the global resource
 *
 * \param id index of the Ifx_GlobalResources_Item in the table, the index starts with 0
 *
 * \return return Ifx_GlobalResources_Item.resource
 */
IFX_EXTERN void *Ifx_GlobalResources_get(sint32 id);

/** \brief Returns the global resource index.
 *
 * \return Returns the global resource index, -1 if not found
 */
IFX_EXTERN sint32 Ifx_GlobalResources_getIndex(void *resource);

/** Return a pointer to the global resource item
 *
 * \param id index of the Ifx_GlobalResources_Item in the table, the index starts with 0
 *
 * \return return the Ifx_GlobalResources_Item
 */
IFX_EXTERN const Ifx_GlobalResources_Item *Ifx_GlobalResources_getItem(sint32 id);

/** Return a the resource name as an NULL terminated string
 *
 * \param id index of the Ifx_GlobalResources_Item in the table, the index starts with 0
 *
 * \return return Ifx_GlobalResources_Item.name
 */
IFX_EXTERN pchar Ifx_GlobalResources_getName(sint32 id);

/** Initialize the global resource handler
 *
 * \param table pointer to an array of Ifx_GlobalResources_Item
 * \param size number of item in the table corresponds to sizeof(table)
 *
 * return returns TRUE in case of success else FALSE
 *
 */
IFX_EXTERN boolean Ifx_GlobalResources_init(const Ifx_GlobalResources_Item *table, uint32 size);
/** \} */

#endif /* IFX_GLOBALRESOURCES_H */