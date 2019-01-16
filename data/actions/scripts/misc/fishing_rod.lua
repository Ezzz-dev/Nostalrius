local water = {
	4597, 4598, 4599, 4600, 4601, 4602,
	4609, 4610, 4611, 4612, 4613, 4614,
	4615, 4616, 4617, 4618, 4619, 4620,
	622
}

local fishableWater = {
	4597, 4598, 4599, 4600, 4601, 4602
}

function onUse(player, item, fromPosition, target, toPosition)
	if not target:isItem() then
		return false
	end
	
	if not table.contains(water, target:getId()) then
		return false
	end
	
	if not Tile(player:getPosition()):hasFlag(TILESTATE_PROTECTIONZONE) then
		if player:getItemCount(3492) >= 1 then
			player:addSkillTries(SKILL_FISHING, 1)
			if math.random(1, 100) <= math.min(math.max(10 + (player:getEffectiveSkillLevel(SKILL_FISHING) - 10) * 0.597, 10), 50) then
				player:addItem(3578, 1)
				
				if target:getId() ~= 622 then
					target:transform(4609, 1)
				end
				
				target:decay()
				player:removeItem(3492, 1)
			end
		end
	end
	
	target:getPosition():sendMagicEffect(2)
	return true
end
