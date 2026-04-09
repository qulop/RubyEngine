#include "RenderPass.hpp"

#include <vulkan/vk_enum_string_helper.h>
#include <backends/vulkan/core/Device.hpp>


namespace Kiwi::Vulkan {
    Result<RenderPass> RenderPass::Create(const RenderPassCreateInfo& createInfo) {
        RenderPass result;

        VkRenderPassCreateInfo rpCreateInfo = { .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
        rpCreateInfo.attachmentCount = createInfo.attachments.size();
        rpCreateInfo.pAttachments = createInfo.attachments.data();
        rpCreateInfo.subpassCount = createInfo.subpasses.size();
        rpCreateInfo.pSubpasses = createInfo.subpasses.data();

        VkResult err = vkCreateRenderPass(createInfo.device->GetDevice(), &rpCreateInfo, nullptr, &result.renderPass);
        if (err != VK_SUCCESS) {
            return Error {
                .kind = EGeneralError::CREATE_FAIL,
                .desc = string_VkResult(err)
            };
        }

        return Success(result);
    }
}
