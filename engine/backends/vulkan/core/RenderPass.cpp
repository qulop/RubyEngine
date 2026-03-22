#include "RenderPass.hpp"

#include <backends/vulkan/core/Device.hpp>


namespace Kiwi::Vulkan {
    Result<RenderPass, EGeneralError> RenderPass::Create(const RenderPassCreateInfo& createInfo) {
        RenderPass result;

        VkRenderPassCreateInfo rpCreateInfo = { .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
        rpCreateInfo.attachmentCount = createInfo.attachments.size();
        rpCreateInfo.pAttachments = createInfo.attachments.data();
        rpCreateInfo.subpassCount = createInfo.subpasses.size();
        rpCreateInfo.pSubpasses = createInfo.subpasses.data();

        VkResult err = vkCreateRenderPass(createInfo.device->GetDevice(), &rpCreateInfo, nullptr, &result.renderPass);
        if (err != VK_SUCCESS) {

        }

        return result;
    }
}
