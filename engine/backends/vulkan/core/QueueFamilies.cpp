#include "QueueFamilies.hpp"

#include <backends/vulkan/core/CreateInfo.hpp>
#include <backends/vulkan/core/VulkanTypes.hpp>


namespace Kiwi::Vulkan {
    QueueFamilyIndices QueueFamilyIndices::Find(VkPhysicalDevice physicalDevice, const Surface& surface) {
        QueueFamilyIndices indices;

        u32 count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);

        Vector<VkQueueFamilyProperties> families(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, families.data());

        for (i32 i : std::views::iota(families.size())) {
            VkQueueFlags queueFlags = families.at(i).queueFlags;

            if (queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicQueueIndex = i;
            }
            if (surface.DoesQueueSupportPresentation(physicalDevice, i)) {
                indices.presentationQueueIndex = i;
            }


            if (indices.AllIndicesComplete()) {
                break;
            }
        }

        return indices;
    }

    std::set<i32> QueueFamilyIndices::GetUniqueIndices() const {
        return std::set{
            graphicQueueIndex, presentationQueueIndex
        };
    }

    bool QueueFamilyIndices::AllIndicesComplete() const {
        return graphicQueueIndex != KIWI_VK_UNDEFINED_ID &&  presentationQueueIndex != KIWI_VK_UNDEFINED_ID;
    }



    VkDeviceQueueCreateInfo DeviceQueues::GetCreateInfo(i32 idx, const float *priority) {
        auto createInfo = GetBasicCreateInfo<VkDeviceQueueCreateInfo>(VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO);
        createInfo.queueFamilyIndex = idx;
        createInfo.queueCount = 1;
        createInfo.pQueuePriorities = priority;

        return createInfo;
    }

    Opt<DeviceQueues> DeviceQueues::Create(VkDevice device, QueueFamilyIndices indices) {
        if (!indices.AllIndicesComplete()) {
            return nullopt;
        }

        DeviceQueues queues;

        vkGetDeviceQueue(device, indices.graphicQueueIndex, 0, &queues.graphicQueue);
        vkGetDeviceQueue(device, indices.presentationQueueIndex, 0, &queues.presentationQueue);

        return queues;
    }

    bool DeviceQueues::IsValid() const {
        return graphicQueue != VK_NULL_HANDLE && presentationQueue != VK_NULL_HANDLE;
    }
}
