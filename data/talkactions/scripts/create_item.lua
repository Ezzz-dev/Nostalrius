function onSay(player, words, param)
	if not player:getGroup():getAccess() then
		return true
	end

	if player:getAccountType() < ACCOUNT_TYPE_GOD then
		return false
	end

	local split = param:split(",")

	local itemType = ItemType(split[1])
	if itemType:getId() == 0 then
		itemType = ItemType(tonumber(split[1]))
		if itemType:getId() == 0 then
			player:sendCancelMessage("There is no item with that id or name.")
			return false
		end
	end

	local keynumber = 0
	local count = tonumber(split[2])
	if count ~= nil then
		if itemType:isStackable() then
			count = math.min(10000, math.max(1, count))
		elseif itemType:isKey() then
			keynumber = count
			count = 1
		elseif not itemType:hasSubType() then
			count = math.min(100, math.max(1, count))
		else
			count = math.max(1, count)
		end
	else
		count = 1
	end

	local result = player:addItem(itemType:getId(), count)
	if result ~= nil then
		if not itemType:isStackable() then
			if type(result) == "table" then
				for _, item in ipairs(result) do
					if itemType:isKey() then
						item:setAttribute(ITEM_ATTRIBUTE_KEYNUMBER, keynumber)
					end
					item:decay()
				end
			else
				if itemType:isKey() then
					result:setAttribute(ITEM_ATTRIBUTE_KEYNUMBER, keynumber)
				end
				result:decay()
			end
		end

		player:getPosition():sendMagicEffect(CONST_ME_MAGIC_GREEN)
	end
	return false
end
